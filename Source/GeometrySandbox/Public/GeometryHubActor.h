// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"

#include "GeometryHubActor.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)

USTRUCT()
struct FGeometryPayload
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere)
    TSubclassOf<ABaseGeometryActor> GeometryClass;

    UPROPERTY(EditAnywhere)
    FGeometryData Data;

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
    
    //All UClass Classes
    //UPROPERTY(EditAnywhere)
    //UClass* Class;

    //All ABaseGeometry Instances
    //UPROPERTY(EditAnywhere)
    //ABaseGeometryActor* GeometryObject;

    UPROPERTY(EditAnywhere)
    TSubclassOf<ABaseGeometryActor> GeometryClass;
    
    UPROPERTY(EditAnywhere)
    TArray<FGeometryPayload> GeometryPayloads;

public:    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    void DoActorSpawn1();
    void DoActorSpawn2();
    void DoActorSpawn3();

    void OnColorChanged(const FLinearColor& Color, const FString& Name);
    void OnTimerFinished(AActor* Actor);
};
