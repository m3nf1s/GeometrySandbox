// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
    if (BaseMesh)
    {
        SetRootComponent(BaseMesh);
    }
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
    Super::BeginPlay();

    InitialLocation = GetActorLocation();

    SetColor(GeometryData.Color);

    PrintStringTypes();
    PrintUELOGExample();
    PrintTypes();
    PrintActorInformation();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Move();
}

void ABaseGeometryActor::PrintTypes()
{
    UE_LOG(LogBaseGeometry, Warning, TEXT("Name: %s"), *GetName());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Weapon number: %d, Kills number: %i"), WeaponNumber, KillsNumber);
    UE_LOG(LogBaseGeometry, Warning, TEXT("Health: %f"), Health);
    UE_LOG(LogBaseGeometry, Warning, TEXT("Player is dead %d"), IsDead);
    UE_LOG(LogBaseGeometry, Warning, TEXT("Player has ultimate %i"), static_cast<int>(HasUltimate));
}

void ABaseGeometryActor::PrintUELOGExample()
{
    UE_LOG(LogTemp, Display, TEXT("Hello, Unreal!"));
    UE_LOG(LogTemp, Warning, TEXT("Hello, Unreal!"));
    UE_LOG(LogTemp, Error, TEXT("Hello, Unreal!"));
}

void ABaseGeometryActor::PrintStringTypes()
{
    UE_LOG(LogBaseGeometry, Display, TEXT("%s"), *Name);

    FString WeaponNumberStat = FString::FromInt(WeaponNumber);
    FString HealthStat = FString::SanitizeFloat(Health);
    FString IsDeadStat = FString(IsDead ? "true" : "false");
    FString Stats = FString::Printf(TEXT("== ALL STATS ==\n%s\n%s\n%s"), *WeaponNumberStat, *HealthStat, *IsDeadStat);
    UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stats);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::White, Name);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Stats, true, FVector2D(1.5f, 1.5f));
    }
}

void ABaseGeometryActor::PrintActorInformation()
{
    FTransform Transform = GetActorTransform();
    FVector Location = Transform.GetLocation();
    FRotator Rotation = Transform.Rotator();
    FVector Scale = Transform.GetScale3D();

    UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name: %s"), *GetName());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Transform: %s"), *Transform.ToString());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Location: %s"), *Location.ToString());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Rotation: %s"), *Rotation.ToString());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Scale: %s"), *Scale.ToString());

    UE_LOG(LogBaseGeometry, Error, TEXT("Human readable transform: %s\n"), *Transform.ToHumanReadableString());
}

void ABaseGeometryActor::Move()
{
    FVector CurrentLocation = GetActorLocation();
    UWorld* World = GetWorld();
    if (World)
    {
        const float Time = GetWorld()->GetTimeSeconds();

        switch (GeometryData.MoveType)
        {
        case EMovementType::Sin:
            CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Cos(GeometryData.Frequency * Time);
            break;
        case EMovementType::Cos:
            CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
            break;
        default:
            break;
        }
        
        SetActorLocation(CurrentLocation);
    }
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
{
    if (BaseMesh)
    {
        UMaterialInstanceDynamic* DynMaterialInstance = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
        if (DynMaterialInstance)
        {
            DynMaterialInstance->SetVectorParameterValue("Color", Color);
        }
    }
}
