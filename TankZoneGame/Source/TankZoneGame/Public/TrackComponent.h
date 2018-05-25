// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TrackComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKZONEGAME_API UTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable)
	void TrackAccelerate(float Throttle);
	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 40000000.f;
	
};
