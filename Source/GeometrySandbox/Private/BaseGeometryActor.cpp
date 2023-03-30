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

	PrintUELOGExample();
	PrintTypes();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGeometryActor::PrintTypes()
{
	int WeaponNumber = 42;
	int KillsNumber = 4;
	float Health = 34.5278f;
	bool IsDead = false;
	bool HasUltimate = true;

	UE_LOG(LogTemp, Display, TEXT("Weapon number: %d, Kills number: %i"), WeaponNumber, KillsNumber);
	UE_LOG(LogTemp, Display, TEXT("Health: %.2f"), Health);
	UE_LOG(LogTemp, Display, TEXT("Player is dead %d"), IsDead);
	UE_LOG(LogTemp, Display, TEXT("Player has ultimate %i"), static_cast<int>(HasUltimate));
}

void ABaseGeometryActor::PrintUELOGExample()
{
	UE_LOG(LogTemp, Display, TEXT("Hello, Unreal!"));
	UE_LOG(LogTemp, Warning, TEXT("Hello, Unreal!"));
	UE_LOG(LogTemp, Error, TEXT("Hello, Unreal!"));
}

