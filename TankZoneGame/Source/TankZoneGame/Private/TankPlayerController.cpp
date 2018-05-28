// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include"AimingComponent.h"
#include"Runtime/Engine/Classes/Engine/World.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetPawn())
	{
		TankAimingComponent = GetPawn()->FindComponentByClass<UAimingComponent>();
		if(TankAimingComponent)
			FoundAimingComponent(TankAimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector HitLocation;
	if (AimTowardsCrossHair(HitLocation))
	{
		if (GetPawn())
		{
			TankAimingComponent->AimingLog(HitLocation);
		}
	}
}

bool ATankPlayerController::AimTowardsCrossHair(FVector &HitLocation)
{
	
	if (GetSightRayHitLocation(HitLocation))
	{
		return true;
	}
	else
	return false;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX*ScreenX, ViewportSizeY*ScreenY);
	FVector WorldLocation, WorldDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection))
	{
		if (Raycast(WorldDirection, HitLocation))
		{
			return true;
		}
	}
	return false;
}
bool ATankPlayerController::Raycast(FVector LookDirection, FVector& HitLocation)
{
	FHitResult HitResult;
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + LookDirection * ProjectileRange;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}