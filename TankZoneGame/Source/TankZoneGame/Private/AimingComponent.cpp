// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include"TankTurretComponent.h"
#include"BarrelComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"


void UAimingComponent::MoveTurret(FVector AimLocation)
{
}

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UAimingComponent::AimingLog(FVector AimLocation,float LaunchSpeed)
{
	if(!TankBarrel)
	{
		return;
	}
	FVector LaunchVelocity;
	FVector StartLocation=TankBarrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, AimLocation, LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s :Aim Solution found for %s"), *LaunchVelocity.GetSafeNormal().ToString(), *GetOwner()->GetName())
		MoveAimTo(LaunchVelocity.GetSafeNormal());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No solution for %s"), *GetOwner()->GetName())
	}

}

void UAimingComponent::BarrelSetter(UBarrelComponent* Barrel)
{
	TankBarrel = Barrel;
}

void UAimingComponent::TurretSetter(UTankTurretComponent * Turret)
{
	TankTurret = Turret;
}

void UAimingComponent::MoveAimTo(FVector AimTurretto)
{
	FRotator AimRotator = AimTurretto.Rotation();
	FRotator CurrentRotation = TankBarrel->GetForwardVector().Rotation();
	FRotator DeltaRotation =AimRotator - CurrentRotation;;
	TankTurret->AimTurret(DeltaRotation.Yaw);
	TankBarrel->Elevate(DeltaRotation.Pitch);
}
