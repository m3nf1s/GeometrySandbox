// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
    : BaseMesh(CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh"))
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
    SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
    Super::BeginPlay();

    InitialLocation = GetActorLocation();

    SetColor(GeometryData.Color);

    GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);
    
    //PrintTransform();
    //PrintStringTypes();
    //PrintTypes();
}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UE_LOG(LogBaseGeometry, Error, TEXT("Actor is dead %s"), *GetName());
    Super::EndPlay(EndPlayReason);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    HandleMovement();
}

void ABaseGeometryActor::PrintTypes() const
{
    UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Weapons num: %d, kills num: %d"), WeaponNum, KillsNum);
    UE_LOG(LogBaseGeometry, Warning, TEXT("Health: %f"), Health);
    UE_LOG(LogBaseGeometry, Warning, TEXT("IsDead: %d, HasWeapon: %d"), IsDead, static_cast<int32>(HasWeapon));
}

void ABaseGeometryActor::PrintStringTypes() const
{
    FString Name = "John Connor";
    UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s"), *Name)

    FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponNum);
    FString HealthStr     = "Health = "      + FString::SanitizeFloat(Health);
    FString IsDeadStr     = "Is Dead = "     + FString(IsDead ? "true" : "false");

    FString Stat = FString::Printf(TEXT(" \n== All stats ==\n%s\n%s\n%s"), *WeaponsNumStr, *HealthStr, *IsDeadStr);
    UE_LOG(LogBaseGeometry, Error, TEXT("%s"), *Stat);

    if(GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, Name);
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Stat, true, FVector2D(1.5f, 1.5f));
    }
}

void ABaseGeometryActor::PrintTransform() const
{
    FTransform Transform = GetActorTransform();
    FVector    Location  = Transform.GetLocation();
    FRotator   Rotation  = Transform.Rotator();
    FVector    Scale     = Transform.GetScale3D();
    
    UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Transform %s"), *Transform.ToString());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Location %s"), *Location.ToString());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Rotation %s"), *Rotation.ToString());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Scale %s"), *Scale.ToString());

    UE_LOG(LogBaseGeometry, Error, TEXT("Human Transform %s"), *Transform.ToHumanReadableString());
}

void ABaseGeometryActor::MoveSin()
{
    FVector CurrentLocation = GetActorLocation();
    
    if(GetWorld())
    {
        const float Time = GetWorld()->GetTimeSeconds();
        CurrentLocation.Y = InitialLocation.Y + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
        SetActorLocation(CurrentLocation);
    }
}

void ABaseGeometryActor::MoveCos()
{
    FVector CurrentLocation = GetActorLocation();
    
    if(GetWorld())
    {
        const float Time = GetWorld()->GetTimeSeconds();
        CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Cos(GeometryData.Frequency * Time);
        SetActorLocation(CurrentLocation);
    }
}

void ABaseGeometryActor::MoveCircle()
{
    FVector CurrentLocation = GetActorLocation();
    
    if(GetWorld())
    {
        const float Time = GetWorld()->GetTimeSeconds();
        CurrentLocation.Y = InitialLocation.Y + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
        CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Cos(GeometryData.Frequency * Time);
        SetActorLocation(CurrentLocation);
    }
}

void ABaseGeometryActor::HandleMovement()
{
    switch (GeometryData.MoveType)
    {
        case EMovementType::Sin:
        {
            MoveSin();
            break;
        }

        case EMovementType::Cos:
        {
            MoveCos();
            break;
        }
        
        case EMovementType::Circle:
        {
            MoveCircle();
            break;
        }
        
        case EMovementType::Static: break;
        
        default: break;
    }
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color) const
{
    if(!BaseMesh) return;
    
    UMaterialInstanceDynamic* DynamicMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);

    if(DynamicMaterial)
    {
        DynamicMaterial->SetVectorParameterValue("Color", Color);
    }
}

FString ABaseGeometryActor::GeometryDataToString() const
{ 
    FString MoveTypeString;
    switch (GeometryData.MoveType)
    {
        case EMovementType::Static:
        {
            MoveTypeString = "Static";
            break;
        }
        case EMovementType::Sin:
        {
            MoveTypeString = "Sin";
            break;
        }
        case EMovementType::Cos:
        {
            MoveTypeString = "Cos";
            break;
        }
        case EMovementType::Circle:
        {
            MoveTypeString = "Circle";
            break;
        }
    }
    
    return FString::Printf(TEXT("Amplitude: %f, Frequency: %f, Move Type: %s, Color: %s, Time Rate: %f"),
        GeometryData.Amplitude, GeometryData.Frequency, *MoveTypeString, *GeometryData.Color.ToString(), GeometryData.TimerRate);
}

void ABaseGeometryActor::OnTimerFired()
{
    if(++TimerCount <= MaxTimerCount)
    {
        const FLinearColor NewColor = FLinearColor::MakeRandomColor();
        UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s, Timer Count: %d, Color to set up %s"), *GetName(), TimerCount, *NewColor.ToString());
        SetColor(NewColor);
        OnColorChanged.Broadcast(NewColor, GetName());
    }
    else
    {
        UE_LOG(LogBaseGeometry, Warning, TEXT("Name: %s, Time has been stopped!"), *GetName());
        GetWorldTimerManager().ClearTimer(TimerHandle);
        OnTimeFinished.Broadcast(this);
    }
}

void ABaseGeometryActor::SetGeometryData(const FGeometryData& Data)
{
    GeometryData = Data;
}

FGeometryData ABaseGeometryActor::GetGeometryData() const
{
    return GeometryData;
}
