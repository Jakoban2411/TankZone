// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"
class UTrackComponent;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKZONEGAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void MoveDirection(float direction);
	UFUNCTION(BlueprintCallable)
	void SetTracks(UTrackComponent* RightTrackToSet,UTrackComponent* LeftTrackToSet);
	UFUNCTION(BlueprintCallable)
	void MoveRight(float direction);
	UTrackComponent* RightTrack;
	UTrackComponent* LeftTrack;
	virtual void RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) override;
};
