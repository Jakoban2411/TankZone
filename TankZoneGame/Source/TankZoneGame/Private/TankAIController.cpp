// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include"AimingComponent.h"
#include"Engine/World.h"
#include"Tank.h"
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
		if(TankAimingComponent->CurrentAimStatus()==EAimStatus::LOCKED)
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

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp,Warning,TEXT("Some AI died"))
}

void ATankAIController::SetPawn(APawn * InPawn)
{

	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}
