// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include"Runtime/Engine/Classes/Engine/World.h"

ATank * ATankPlayerController::GetControlledTank()
{
		return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetControlledTank())
	{
		ATank* ControlledTank = GetControlledTank();
		UE_LOG(LogTemp, Warning, TEXT("The Tank Possessed By Player Is %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
	if (GetControlledTank())
	{
		//GetControlledTank()->AimAt(HitLocation);
	}
}

void ATankPlayerController::AimTowardsCrossHair()
{
	
	if (GetSightRayHitLocation(HitLocation))
	{
	}
	else
	UE_LOG(LogTemp, Warning, TEXT("Aim NOT Successfull"));
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
