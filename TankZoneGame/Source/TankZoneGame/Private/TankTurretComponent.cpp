// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"
#include "Engine/World.h"

void UTankTurretComponent::AimTurret(float RotationPerSecond)
{
	RotationPerSecond = FMath::Clamp<float>(RotationPerSecond, -1.f, 1.f);
	float RotationChangePerFrame = RotationPerSecond * MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	float RotationAddedThisFrame = RelativeRotation.Yaw + RotationChangePerFrame;
	SetRelativeRotation(FRotator(0.f,RotationAddedThisFrame,0.f));
}
