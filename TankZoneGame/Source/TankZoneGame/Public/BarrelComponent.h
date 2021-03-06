// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "BarrelComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKZONEGAME_API UBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Elevate(float RelativeSpeed);
	UPROPERTY(EditAnywhere)
		float MaxDegreesPerSecond = 20.f;
	UPROPERTY(EditAnywhere)
		float MaxElevation = 35.f;
	UPROPERTY(EditAnywhere)
		float MinElevation = 0.f;
};
