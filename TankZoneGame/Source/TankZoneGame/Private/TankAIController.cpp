// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include"TankPlayerController.h"
#include"Tank.h"
#include"Engine/World.h"

ATank * ATankAIController::GetAITank()
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if (GetPlayer())
	{
		ATankPlayerController* PlayerController = GetPlayer();
		UE_LOG(LogTemp, Warning, TEXT("AI looking for %s"), *(PlayerController->GetName()))
	}
}

void ATankAIController::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	if (GetPlayer())
	{
		AimAtPlayer();
	}
}

ATankPlayerController* ATankAIController::GetPlayer()
{
	return Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
}

void ATankAIController::AimAtPlayer()
{
	if (GetPlayer())
	{
		ATank* PlayerTank = GetPlayer()->GetControlledTank();
		if (GetAITank())
		{
			GetAITank()->AimAt(PlayerTank->GetActorLocation());
		}
	}
}
