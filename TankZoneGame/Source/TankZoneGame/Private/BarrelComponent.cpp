// Fill out your copyright notice in the Description page of Project Settings.

#include "BarrelComponent.h"
#include"Engine/World.h"
void UBarrelComponent::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float ElevationChangePerFrame = RelativeSpeed * MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	float ElevationAddedThisFrame = RelativeRotation.Pitch + ElevationChangePerFrame;
	float ClampedElevation=FMath::Clamp<float>(ElevationAddedThisFrame, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(ClampedElevation,0.f,0.f));
}
