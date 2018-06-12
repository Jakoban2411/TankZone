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
	if (PlayerTank)
	{
		
		MoveToActor(PlayerTank, AcceptanceRadius);
		TankAimingComponent->AimingLog(PlayerTank->GetActorLocation());
		if(TankAimingComponent->CurrentAimStatus()==EAimStatus::LOCKED)
		TankAimingComponent->Fire();
	}
}




void ATankAIController::OnTankDeath()
{

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
