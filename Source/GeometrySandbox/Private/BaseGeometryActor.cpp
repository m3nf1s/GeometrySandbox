// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

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

	PrintStringTypes();
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
	UE_LOG(LogBaseGeometry, Warning, TEXT("Name: %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Weapon number: %d, Kills number: %i"), WeaponNumber, KillsNumber);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Health: %f"), Health);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Player is dead %d"), IsDead);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Player has ultimate %i"), static_cast<int>(HasUltimate));
}

void ABaseGeometryActor::PrintUELOGExample()
{
	UE_LOG(LogTemp, Display, TEXT("Hello, Unreal!"));
	UE_LOG(LogTemp, Warning, TEXT("Hello, Unreal!"));
	UE_LOG(LogTemp, Error, TEXT("Hello, Unreal!"));
}

void ABaseGeometryActor::PrintStringTypes()
{
	UE_LOG(LogBaseGeometry, Display, TEXT("%s"), *Name);

	FString WeaponNumberStat = FString::FromInt(WeaponNumber);
	FString HealthStat = FString::SanitizeFloat(Health);
	FString IsDeadStat = FString(IsDead ? "true" : "false");
	FString Stats = FString::Printf(TEXT("== ALL STATS ==\n%s\n%s\n%s"), *WeaponNumberStat, *HealthStat, *IsDeadStat);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stats);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::White, Name);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Stats, true, FVector2D(1.5f, 1.5f));
	}
}

