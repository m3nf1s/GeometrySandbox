// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	PrintTypes();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseGeometryActor::PrintTypes()
{
	int32 WeaponNum = 4;	
	int32 KillsNum  = 7;
	float Health    = 67.589123f;
	bool  isDead    = false;
	bool  HasWeapon = true;

	UE_LOG(LogTemp, Display, TEXT("Weapons num: %d, kills num: %d"), WeaponNum, KillsNum);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	UE_LOG(LogTemp, Display, TEXT("Health: %.3f"), Health);
	UE_LOG(LogTemp, Error,   TEXT("IsDead: %d, HasWeapon: %d"), isDead, HasWeapon);
}