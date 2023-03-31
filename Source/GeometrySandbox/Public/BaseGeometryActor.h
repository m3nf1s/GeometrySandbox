// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

#include "BaseGeometryActor.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
    Static,
    Sin,
    Cos
};

USTRUCT()
struct FGeometryData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, Category = "Movement")
    float Amplitude = 50.0f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float Frequency = 2.0f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    EMovementType MoveType = EMovementType::Static;

    UPROPERTY(EditAnywhere, Category = "Design")
    FLinearColor Color = FLinearColor::Black;
};

UCLASS()
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABaseGeometryActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    void PrintTypes();
    void PrintUELOGExample();
    void PrintStringTypes();
    void PrintActorInformation();

    void Move();
    void SetColor(const FLinearColor& Color);

public:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* BaseMesh;

protected:
    UPROPERTY(EditAnywhere, Category = "Geometry")
    FGeometryData GeometryData;

    UPROPERTY(EditInstanceOnly, Category = "Stats")
    FString Name = "Joseph Rostenkovic";

    UPROPERTY(EditAnywhere, Category = "Weapon")
    int32 WeaponNumber = 42;

    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    int32 KillsNumber = 4;

    UPROPERTY(EditInstanceOnly, Category = "Health")
    float Health = 34.5278f;

    UPROPERTY(EditAnywhere, Category = "Health")
    bool IsDead = false;

    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    bool HasUltimate = true;

private:
    FVector InitialLocation;
};