// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include"TrackComponent.h"
void UTankMovementComponent::MoveDirection(float direction)
{
	RightTrack->SetThrottle(direction);
	LeftTrack->SetThrottle(direction);
}

void UTankMovementComponent::SetTracks(UTrackComponent * RightTrackToSet, UTrackComponent * LeftTrackToSet)
{
	RightTrack = RightTrackToSet;
	LeftTrack = LeftTrackToSet;
}

void UTankMovementComponent::MoveRight(float direction)
{
	RightTrack->SetThrottle(direction*1.35);
	LeftTrack->SetThrottle(-direction*1.35);		
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