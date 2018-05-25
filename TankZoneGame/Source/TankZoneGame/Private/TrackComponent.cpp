// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackComponent.h"

void UTrackComponent::TrackAccelerate(float Throttle)
{
	FVector ForceApplied = GetForwardVector()*Throttle*MaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	UE_LOG(LogTemp,Warning,TEXT("%s Force Applied to %s at Location %s"),*(ForceApplied.ToString()),*GetName(), *(ForceLocation.ToString()))
}
