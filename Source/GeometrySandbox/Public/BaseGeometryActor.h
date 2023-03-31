// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);

UENUM(BlueprintType)
enum class EMovementType : uint8
{
    Static,
    Circle,
    Vertical,
    Horizontal,
    Max
};

USTRUCT(BlueprintType)
struct FGeometryData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float Amplitude = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float Frequency = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    EMovementType MoveType = EMovementType::Static;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
    FLinearColor Color = FLinearColor::Black;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
    float TimerRate = 3.0f;

    FString ToString() const;
};

UCLASS()
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABaseGeometryActor();

    void SetGeometryData(const FGeometryData& NewData);
    
    UFUNCTION(BlueprintCallable)
    FGeometryData GetGeometryData() const;
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    void PrintTypes() const;
    void PrintUELOGExample() const ;
    void PrintStringTypes() const;
    void PrintActorInformation() const;
    
    void SetColor(const FLinearColor& Color) const;
    
    void Move();
    void OnTimerFired();

public:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* BaseMesh;

    UPROPERTY(BlueprintAssignable)
    FOnColorChanged OnColorChanged;
    FOnTimerFinished OnTimerFinished;

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
    FTimerHandle TimerHandle;

    const int32 MaxTimerCount = 5;
    int32 TimerCount = 0;
};