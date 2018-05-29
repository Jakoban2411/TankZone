// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
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
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank)
	{
		
		MoveToActor(PlayerTank, AcceptanceRadius);
		AimAtPlayer();
		TankAimingComponent->Fire();
	}
}


void ATankAIController::AimAtPlayer()
{
	if (GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (GetPawn())
		{
			TankAimingComponent->AimingLog(PlayerTank->GetActorLocation());
		}
	}
}
