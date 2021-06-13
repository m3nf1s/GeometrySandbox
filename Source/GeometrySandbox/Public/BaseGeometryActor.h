// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "BaseGeometryActor.generated.h"

UCLASS()
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABaseGeometryActor();

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* BaseMesh;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    void PrintTypes();
    void PrintStringTypes();
    void PrintTransform();

protected:
    UPROPERTY(EditAnywhere, Category = "Weapon")
    int32 WeaponNum = 4;

    UPROPERTY(EditDefaultsOnly, Category = "Stat")
    int32 KillsNum  = 7;

    UPROPERTY(EditInstanceOnly, Category = "Health")
    float Health    = 67.589123f;

    UPROPERTY(EditAnywhere, Category = "Health")
    bool  IsDead    = false;

    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    bool  HasWeapon = true;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float Amplitude = 50.0f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float Frequency = 2.0f;

private:
    FVector InitialLocation;
};
