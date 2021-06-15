// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
    Super::BeginPlay();

    DoActorSpawn1();
    DoActorSpawn2();
    DoActorSpawn3();
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGeometryHubActor::DoActorSpawn1() const
{
    UWorld* World = GetWorld();
    if(World)
    {
        for(int32 i = 0; i < 10; ++i)
        {
            const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(-1800.0f, 100.0f * i * 6, 300.0f));
            ABaseGeometryActor* Geometry       = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);
            if(Geometry)
            {
                FGeometryData Data;
                Data.Amplitude = FMath::RandRange(100.0f,200.0f);
                Data.Frequency = FMath::RandRange(2.0f, 5.0f);
                Data.MoveType  = static_cast<EMovementType>(FMath::RandRange(0, 3));
                Geometry->SetGeometryData(Data);
            }
        }
    }
}

void AGeometryHubActor::DoActorSpawn2() const
{
    UWorld* World = GetWorld();
    if(World)
    {
        for(int32 i = 0; i < 10; ++i)
        {
            const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(-1800.0f, 100.0f * i * 6, 900.0f));
            ABaseGeometryActor* Geometry       = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);
            if(Geometry)
            {
                FGeometryData Data;
                Data.Color     = FLinearColor::Yellow;
                Data.Amplitude = FMath::RandRange(100.0f,200.0f);
                Data.Frequency = FMath::RandRange(2.0f, 5.0f);
                Data.MoveType  = static_cast<EMovementType>(FMath::RandRange(0, 3));
                Geometry->SetGeometryData(Data);
                Geometry->FinishSpawning(GeometryTransform);
            }
        }
    }
}

void AGeometryHubActor::DoActorSpawn3() const
{
    UWorld* World = GetWorld();
    if(World)
    {
        for(const FGeometryPayload& Payload : GeometryPayloads)
        {
            ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform);
            if(Geometry)
            {
                Geometry->SetGeometryData(Payload.Data);
                Geometry->FinishSpawning(Payload.InitialTransform);
            }
        }
    }
}

