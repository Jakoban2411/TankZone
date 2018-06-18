// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include"TankTurretComponent.h"
#include"BarrelComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include"Projectile.h"
#include"Runtime/Engine/Classes/Engine/World.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (Ammo<= 0)
	{
		FiringStatus = EAimStatus::NOAMMO;
	}
	else
	if ((FPlatformTime::Seconds() - LastLaunchTime) < ReloadTime)
		FiringStatus = EAimStatus::RELOADING;
	else
	{
		if (isBarrelMoving())
		{
			FiringStatus = EAimStatus::AIMING;	
		}
		else
		{
			FiringStatus = EAimStatus::LOCKED;
		}
	}
}

void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastLaunchTime = FPlatformTime::Seconds();
}

bool UAimingComponent::isBarrelMoving()
{
	FVector TankAim = TankBarrel->GetForwardVector();
	if (TankAim.Equals(AimedAt, .01))
	{
			return false;
	}
	else
		return true;
}


void UAimingComponent::AimingLog(FVector AimLocation)
{
	if (!TankBarrel)
	{
		return;
	}
	FVector LaunchVelocity;
	FVector StartLocation = TankBarrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, AimLocation, LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimedAt = LaunchVelocity.GetSafeNormal();
		MoveAimTo(AimedAt);
	}
}

void UAimingComponent::Initialise(UBarrelComponent* Barrel, UTankTurretComponent * Turret)
{
	TankBarrel = Barrel;
	TankTurret = Turret;
}

void UAimingComponent::MoveAimTo(FVector AimTurretto)
{
	FRotator AimRotator = AimTurretto.Rotation();
	FRotator CurrentRotation = TankBarrel->GetForwardVector().Rotation();
	FRotator DeltaRotation =AimRotator - CurrentRotation;
	if (DeltaRotation.Yaw > 180||DeltaRotation.Yaw <- 180)
		DeltaRotation.Yaw = -(DeltaRotation.Yaw - 180);
	TankTurret->AimTurret(DeltaRotation.Yaw);
	TankBarrel->Elevate(DeltaRotation.Pitch);
}

void UAimingComponent::Fire()
{
	if (!ensure(TankBarrel))
	{
		return;
	}
	if (Ammo != 0)
	{
		if (FiringStatus != EAimStatus::RELOADING)
		{
			AProjectile* LaunchedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, TankBarrel->GetSocketLocation(FName("Projectile")), TankBarrel->GetSocketRotation(FName("Projectile")));
			if (LaunchedProjectile)
			{
				Ammo--;
				LaunchedProjectile->LaunchProjectile(LaunchSpeed);
				LastLaunchTime = FPlatformTime::Seconds();
			}
		}
	}
}

EAimStatus UAimingComponent::CurrentAimStatus()
{
	return FiringStatus;
}

int UAimingComponent::AmmoCount()
{
	return Ammo;
}
