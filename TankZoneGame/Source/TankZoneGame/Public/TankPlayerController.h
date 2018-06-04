// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
class UAimingComponent;
class ATank;
/**
 * 
 */
UCLASS()
class TANKZONEGAME_API ATankPlayerController : public APlayerController
{

	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void FoundAimingComponent(UAimingComponent* AimCompRef);
	UAimingComponent* TankAimingComponent;
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	bool AimTowardsCrossHair(FVector &HitLocation);
	bool GetSightRayHitLocation(FVector &HitLocation);
	float ScreenX = .5f;
	float ScreenY = .3333;
	float ProjectileRange = 100000.f;
	bool Raycast(FVector LookDirection,FVector& HitLocation);
	virtual void SetPawn(APawn* InPawn) override;
	UFUNCTION()
		void OnTankDeath();
};
