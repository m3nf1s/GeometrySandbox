// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

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

protected:
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
};
