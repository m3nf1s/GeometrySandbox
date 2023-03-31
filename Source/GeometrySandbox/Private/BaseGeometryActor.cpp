// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

FString FGeometryData::ToString() const
{
    FString StringMoveType;
    switch (MoveType)
    {
    case EMovementType::Circle:
        StringMoveType = "Circle";
        break;
    case EMovementType::Vertical:
        StringMoveType = "Vertical";
        break;
    case EMovementType::Horizontal:
        StringMoveType = "Horizontal";
        break;
    default:
        StringMoveType = "Static";
        break;
    }
    
    return FString::Printf(TEXT("Amplitude: %s\nFrequency: %s\nMoveType: %s\nColor: %s\nTimeRate: %s"),
        *FString::SanitizeFloat(Amplitude), *FString::SanitizeFloat(Frequency),
        *StringMoveType, *Color.ToString(), *FString::SanitizeFloat(TimerRate));
}

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

void ABaseGeometryActor::SetGeometryData(const FGeometryData& NewData)
{
    GeometryData = NewData;
}

FGeometryData ABaseGeometryActor::GetGeometryData() const
{
    return GeometryData;
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
    Super::BeginPlay();

    //PrintStringTypes();
    //PrintUELOGExample();
    //PrintTypes();
    //PrintActorInformation();

    InitialLocation = GetActorLocation();

    SetColor(GeometryData.Color);

    GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);
}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UE_LOG(LogBaseGeometry, Error, TEXT("Actor is dead: %s"), *GetName());
    Super::EndPlay(EndPlayReason);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Move();
}

void ABaseGeometryActor::PrintTypes() const
{
    UE_LOG(LogBaseGeometry, Warning, TEXT("Name: %s"), *GetName());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Weapon number: %d, Kills number: %i"), WeaponNumber, KillsNumber);
    UE_LOG(LogBaseGeometry, Warning, TEXT("Health: %f"), Health);
    UE_LOG(LogBaseGeometry, Warning, TEXT("Player is dead %d"), IsDead);
    UE_LOG(LogBaseGeometry, Warning, TEXT("Player has ultimate %i"), static_cast<int>(HasUltimate));
}

void ABaseGeometryActor::PrintUELOGExample() const
{
    UE_LOG(LogTemp, Display, TEXT("Hello, Unreal!"));
    UE_LOG(LogTemp, Warning, TEXT("Hello, Unreal!"));
    UE_LOG(LogTemp, Error, TEXT("Hello, Unreal!"));
}

void ABaseGeometryActor::PrintStringTypes() const
{
    UE_LOG(LogBaseGeometry, Display, TEXT("%s"), *Name);

    const FString WeaponNumberStat = FString::FromInt(WeaponNumber);
    const FString HealthStat = FString::SanitizeFloat(Health);
    const FString IsDeadStat = FString(IsDead ? "true" : "false");
    const FString Stats = FString::Printf(TEXT("== ALL STATS ==\n%s\n%s\n%s"), *WeaponNumberStat, *HealthStat, *IsDeadStat);
    UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stats);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::White, Name);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Stats, true, FVector2D(1.5f, 1.5f));
    }
}

void ABaseGeometryActor::PrintActorInformation() const
{
    const FTransform Transform = GetActorTransform();
    const FVector Location = Transform.GetLocation();
    const FRotator Rotation = Transform.Rotator();
    const FVector Scale = Transform.GetScale3D();

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
    const UWorld* World = GetWorld();
    if (World)
    {
        const float Time = GetWorld()->GetTimeSeconds();

        switch (GeometryData.MoveType)
        {
        case EMovementType::Circle:
            CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
            CurrentLocation.Y = InitialLocation.Y + GeometryData.Amplitude * FMath::Cos(GeometryData.Frequency * Time);
            break;
        case EMovementType::Vertical:
            CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
            break;
        case EMovementType::Horizontal:
            CurrentLocation.Y = InitialLocation.Y + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
        default:
            break;
        }
        
        SetActorLocation(CurrentLocation);
    }
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color) const
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

void ABaseGeometryActor::OnTimerFired()
{
    if (++TimerCount < MaxTimerCount)
    {
        const FLinearColor NewColor = FLinearColor::MakeRandomColor();
        SetColor(NewColor);
        UE_LOG(LogBaseGeometry, Warning, TEXT("Name: %s. Timer count: %i. Color to set up: %s"), *GetName(), TimerCount, *NewColor.ToString());
        OnColorChanged.Broadcast(NewColor, GetName());
    }
    else
    {
        GetWorldTimerManager().ClearTimer(TimerHandle);
        UE_LOG(LogBaseGeometry, Warning, TEXT("Name: %s. Timer has been stopped"), *GetName());
        OnTimerFinished.Broadcast(this);
    }
}
