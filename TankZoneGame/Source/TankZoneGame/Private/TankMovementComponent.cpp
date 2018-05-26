// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include"TrackComponent.h"
void UTankMovementComponent::MoveDirection(float direction)
{
	RightTrack->TrackAccelerate(direction);
	LeftTrack->TrackAccelerate(direction);
}

void UTankMovementComponent::SetTracks(UTrackComponent * RightTrackToSet, UTrackComponent * LeftTrackToSet)
{
	RightTrack = RightTrackToSet;
	LeftTrack = LeftTrackToSet;
}

void UTankMovementComponent::MoveRight(float direction)
{
	RightTrack->TrackAccelerate(direction);
	LeftTrack->TrackAccelerate(0);		
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankDirectionNormal = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector MoveRequestNormal = MoveVelocity.GetSafeNormal();
	MoveDirection(FVector::DotProduct(TankDirectionNormal, MoveRequestNormal));
	auto RotationMove=FVector::CrossProduct(TankDirectionNormal, MoveRequestNormal);
	MoveRight(RotationMove.Z);
	
}
