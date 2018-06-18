// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include"TrackComponent.h"
void UTankMovementComponent::MoveDirection(float direction)
{
	RightTrack->Accelerate(direction*25);
	LeftTrack->Accelerate(direction*25);
	
}

void UTankMovementComponent::SetTracks(UTrackComponent * RightTrackToSet, UTrackComponent * LeftTrackToSet)
{
	RightTrack = RightTrackToSet;
	LeftTrack = LeftTrackToSet;
}

void UTankMovementComponent::MoveRight(float direction)
{
	RightTrack->Accelerate(direction*25);
	LeftTrack->Accelerate(-direction*25);
}
void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankDirectionNormal = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector MoveRequestNormal = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankDirectionNormal, MoveRequestNormal);
	MoveDirection(ForwardThrow);
	auto RotationMove=FVector::CrossProduct(TankDirectionNormal, MoveRequestNormal).Z;
	MoveRight(RotationMove);
}
