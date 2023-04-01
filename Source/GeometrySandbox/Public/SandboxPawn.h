// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SandboxPawn.generated.h"

class UCameraComponent;

UCLASS()
class GEOMETRYSANDBOX_API ASandboxPawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ASandboxPawn();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void PossessedBy(AController* NewController) override;
    virtual void UnPossessed() override;

public:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* SceneComponent;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* StaticMeshComponent;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere)
    float Velocity = 300.0f;

private:
    FVector VelocityVector = FVector::ZeroVector;
 
    void MoveForward(const float Amount);
    void MoveRight(const float Amount);
    void MoveUp(const float Amount);
};
