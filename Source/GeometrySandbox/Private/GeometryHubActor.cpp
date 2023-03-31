// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    // PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
    Super::BeginPlay();

    //DoActorSpawn1();
    //DoActorSpawn2();
    DoActorSpawn3();
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AGeometryHubActor::DoActorSpawn1() const
{
    if(UWorld* World = GetWorld())
    {
        for(int32 i = 0; i < 10; ++i)
        {
            const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 300.0f));
            ABaseGeometryActor* GeometryActor = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);

            if(GeometryActor)
            {
                FGeometryData Data;
                const int32 GeneratedNumber = FMath::RandRange(0, static_cast<int32>(EMovementType::Max));
                Data.MoveType = static_cast<EMovementType>(GeneratedNumber);
                GeometryActor->SetGeometryData(Data);
            }
        }
    }
}

void AGeometryHubActor::DoActorSpawn2() const
{
    if(UWorld* World = GetWorld())
    {
        for(int32 i = 0; i < 10; ++i)
        {
            const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i * 1.25f, 700.0f));
            ABaseGeometryActor* GeometryActor = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);

            if(GeometryActor)
            {
                FGeometryData Data;
                const int32 GeneratedNumber = FMath::RandRange(0, static_cast<int32>(EMovementType::Max));
                Data.MoveType = static_cast<EMovementType>(GeneratedNumber);
                Data.Color = FLinearColor::MakeRandomColor();
                Data.Amplitude = FMath::FRandRange(10.0f, 250.0f);
                Data.Frequency = FMath::FRandRange(0.5f, 3.0f);
                Data.TimerRate = FMath::FRandRange(5.0f, 10.0f);
                GeometryActor->SetGeometryData(Data);
                GeometryActor->FinishSpawning(GeometryTransform);
            }
        }
    }
}

void AGeometryHubActor::DoActorSpawn3()
{
    if(UWorld* World = GetWorld())
    {
        for(const FGeometryPayload& Payload : GeometryPayloads )
        {
            ABaseGeometryActor* GeometryActor = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform);

            if(GeometryActor)
            {
                GeometryActor->SetGeometryData(Payload.GeometryData);
                GeometryActor->FinishSpawning(Payload.InitialTransform);
            }
        }
    }
}

