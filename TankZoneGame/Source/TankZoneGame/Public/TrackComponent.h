// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TrackComponent.generated.h"
class ASuspensionWheel;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKZONEGAME_API UTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
		UTrackComponent();
public:
	
	void Accelerate(float Throttle);
	float CurrentThrottle = 0;
	TArray<ASuspensionWheel*> GetWheels() const;
};
