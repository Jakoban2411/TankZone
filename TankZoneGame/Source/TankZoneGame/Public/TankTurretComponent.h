// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"BarrelComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurretComponent.generated.h"

class UBarrelComponent;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKZONEGAME_API UTankTurretComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
		float MaxDegreesPerSecond = 25.f;
public:
	void AimTurret(float RotationPerSecond);
};
