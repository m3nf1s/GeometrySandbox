// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"

#include "SandboxPawn.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPawn, All, All)

// Sets default values
ASandboxPawn::ASandboxPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
    StaticMeshComponent->SetupAttachment(SceneComponent); //first method
    
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(GetRootComponent()); // second method
}

// Called when the game starts or when spawned
void ASandboxPawn::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ASandboxPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(!VelocityVector.IsZero())
    {
        const FVector NewLocation = GetActorLocation() + VelocityVector * DeltaTime * Velocity;
        SetActorLocation(NewLocation);
        VelocityVector = FVector::ZeroVector;
    }
}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if(PlayerInputComponent)
    {
        PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
        PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);
        PlayerInputComponent->BindAxis("MoveUp", this, &ASandboxPawn::MoveUp);
    }
}

void ASandboxPawn::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    if(!NewController) return;
    UE_LOG(LogSandboxPawn, Error, TEXT("%s possessed %s"), *GetName(), *NewController->GetName());
}

void ASandboxPawn::UnPossessed()
{
    Super::UnPossessed();
    UE_LOG(LogSandboxPawn, Warning, TEXT("%s unpossessed"), *GetName());
}

void ASandboxPawn::MoveForward(float Amount)
{
    UE_LOG(LogSandboxPawn, Display, TEXT("Move forward %f"), Amount);
    VelocityVector.X = Amount;
}

void ASandboxPawn::MoveRight(float Amount)
{
    UE_LOG(LogSandboxPawn, Display, TEXT("Move right %f"), Amount);
    VelocityVector.Y = Amount;
}

void ASandboxPawn::MoveUp(const float Amount)
{
    UE_LOG(LogSandboxPawn, Display, TEXT("Move Up %f"), Amount);
    VelocityVector.Z = Amount;
}

