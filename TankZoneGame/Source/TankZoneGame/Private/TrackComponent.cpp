// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackComponent.h"
#include"Engine/World.h"
#include"SuspensionWheel.h"
#include"SpawnSuspensionComponent.h"
UTrackComponent::UTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UTrackComponent::Accelerate(float Throttle)
{
	auto Wheels = GetWheels();
	for (ASuspensionWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(Throttle);
	}
}

TArray<ASuspensionWheel*> UTrackComponent::GetWheels() const
{

	TArray<USceneComponent*> Children;
	TArray<ASuspensionWheel*> Wheels;
	GetChildrenComponents(false, Children);
	for (USceneComponent* Child : Children)
	{
		if (Cast<USpawnSuspensionComponent>(Child))
		{
			USpawnSuspensionComponent* CastedChild = Cast<USpawnSuspensionComponent>(Child);
			AActor* WheelChild=CastedChild->ReturnChild();
			if (Cast<ASuspensionWheel>(WheelChild))
			{
				auto Wheel = Cast<ASuspensionWheel>(WheelChild);
				Wheels.Add(Wheel);
			}
		}
	}
	return Wheels;
}
