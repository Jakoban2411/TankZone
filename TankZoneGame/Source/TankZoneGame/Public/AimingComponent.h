// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"
class UBarrelComponent;
class UTankTurretComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKZONEGAME_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()
	UBarrelComponent* TankBarrel = nullptr;
	UTankTurretComponent* TankTurret = nullptr;
	void MoveTurret(FVector AimLocation);
public:
	// Sets default values for this component's properties
	UAimingComponent();
	void AimingLog(FVector AimLocation, float LaunchSpeed);
	void BarrelSetter(UBarrelComponent* Barrel);
	void TurretSetter(UTankTurretComponent* Turrert);
	void MoveAimTo(FVector AimTurretto);
};