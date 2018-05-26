// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"
class ATank;
class ATankPlayerController;
/**
 * 
 */
UCLASS()
class TANKZONEGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	ATank* GetAITank();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	ATankPlayerController* GetPlayer();
	void AimAtPlayer();
	UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 3000.f;
};
