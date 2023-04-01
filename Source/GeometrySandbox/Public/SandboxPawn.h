// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SandboxPawn.generated.h"

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

public:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* SceneComponent;

    UPROPERTY(EditAnywhere)
    float Velocity = 300.0f;

private:
    FVector VelocityVector = FVector::ZeroVector;
 
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    
};