// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class TANKZONEGAME_API ATankPlayerController : public APlayerController
{

	GENERATED_BODY()
public:
		ATank* GetControlledTank();
		void BeginPlay() override;
		void Tick(float DeltaTime) override;
		bool AimTowardsCrossHair(FVector &HitLocation);
		bool GetSightRayHitLocation(FVector &HitLocation);
		float ScreenX = .5f;
		float ScreenY = .33333f;
		float ProjectileRange = 100000.f;
		bool Raycast(FVector LookDirection,FVector& HitLocation);
		
};
