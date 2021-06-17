// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChange, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeFinished, AActor*);

UENUM(Blueprintable)
enum class EMovementType : uint8
{
    Static,
    Sin,
    Cos,
    Circle
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

    UPROPERTY(EditAnywhere, Category = "Design")
    float TimerRate = 1.5f;
};

UCLASS()
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABaseGeometryActor();

    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    void SetGeometryData(const FGeometryData& Data);

    FString GeometryDataToString() const;
    
    UFUNCTION(BlueprintCallable)
    FGeometryData GetGeometryData() const;

    UPROPERTY(BlueprintAssignable)
    FOnColorChange OnColorChanged;
    
    FOnTimeFinished OnTimeFinished;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* BaseMesh;

private:
    void    PrintTypes()                        const;
    void    PrintStringTypes()                  const;
    void    PrintTransform()                    const;
    void    SetColor(const FLinearColor& Color) const;

    
    void MoveSin();
    void MoveCos();
    void MoveCircle();
    void HandleMovement();
    void OnTimerFired();

protected:
    UPROPERTY(EditAnywhere, Category = "Weapon")
    int32 WeaponNum = 4;

    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    bool  HasWeapon = true;

    UPROPERTY(EditDefaultsOnly, Category = "Stat")
    int32 KillsNum  = 7;

    UPROPERTY(EditInstanceOnly, Category = "Health")
    float Health    = 67.589123f;

    UPROPERTY(EditAnywhere, Category = "Health")
    bool  IsDead    = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Data")
    FGeometryData GeometryData;

private:
    FVector      InitialLocation;
    FTimerHandle TimerHandle;
    
    const int32  MaxTimerCount = 5;
    int32        TimerCount = 0;
};
