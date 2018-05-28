// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include"TankPlayerController.h"
#include"AimingComponent.h"
#include"Engine/World.h"
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = GetPawn()->FindComponentByClass<UAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	if (GetPlayer())
	{
		MoveToActor(GetPlayer()->GetPawn(), AcceptanceRadius);
		AimAtPlayer();
		TankAimingComponent->Fire();
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
		auto PlayerTank = GetPlayer()->GetPawn();
		if (GetPawn())
		{
			TankAimingComponent->AimingLog(PlayerTank->GetActorLocation());
		}
	}
}
