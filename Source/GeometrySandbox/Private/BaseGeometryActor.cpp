// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include <Engine/Engine.h>

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
    PrintTypes();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseGeometryActor::PrintTypes()
{
    UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Weapons num: %d, kills num: %d"), WeaponNum, KillsNum);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Health: %f"), Health);
	UE_LOG(LogBaseGeometry, Warning, TEXT("IsDead: %d, HasWeapon: %d"), IsDead, static_cast<int32>(HasWeapon));
}

void ABaseGeometryActor::PrintStringTypes()
{
    FString Name = "John Connor";
    UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s"), *Name)

    FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponNum);
    FString HealthStr     = "Health = "      + FString::SanitizeFloat(Health);
    FString IsDeadStr     = "Is Dead = "     + FString(IsDead ? "true" : "false");

    FString Stat = FString::Printf(TEXT(" \n== All stats ==\n%s\n%s\n%s"), *WeaponsNumStr, *HealthStr, *IsDeadStr);
    UE_LOG(LogBaseGeometry, Error, TEXT("%s"), *Stat);

    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, Name);
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Stat, true, FVector2D(1.5f, 1.5f));
}
