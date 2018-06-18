// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include"AimingComponent.h"
#include"Engine/World.h"
#include"Tank.h"
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	TankAimingComponent = GetPawn()->FindComponentByClass<UAimingComponent>();
	auto ControlledTank = GetPawn();
	if (PlayerTank && ControlledTank)
	{
		
		MoveToActor(PlayerTank, AcceptanceRadius);
		TankAimingComponent->AimingLog(PlayerTank->GetActorLocation());
		if(TankAimingComponent->CurrentAimStatus()==EAimStatus::LOCKED)
		TankAimingComponent->Fire();
	}
}




void ATankAIController::OnTankDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy();
	Destroy();
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}
