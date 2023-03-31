// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGeometryActor.h"
#include "GameFramework/Actor.h"
#include "GeometryHubActor.generated.h"

USTRUCT()
struct FGeometryPayload
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere)
    TSubclassOf<ABaseGeometryActor> GeometryClass;

    UPROPERTY(EditAnywhere)
    FGeometryData GeometryData;

    UPROPERTY(EditAnywhere)
    FTransform InitialTransform;
};
UCLASS()
class GEOMETRYSANDBOX_API AGeometryHubActor : public AActor
{
    GENERATED_BODY()

public:	
    // Sets default values for this actor's properties
    AGeometryHubActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(EditAnywhere)
    TSubclassOf<ABaseGeometryActor> GeometryClass;

    UPROPERTY(EditAnywhere)
    TArray<FGeometryPayload> GeometryPayloads;

private:
    void DoActorSpawn1() const;
    void DoActorSpawn2() const;
    void DoActorSpawn3();
};
