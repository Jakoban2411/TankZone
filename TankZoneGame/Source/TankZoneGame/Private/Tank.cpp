// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include"BarrelComponent.h"
#include"AimingComponent.h"
#include"Engine/World.h"
#include"TankMovementComponent.h"
#include"Projectile.h"
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UAimingComponent>(TEXT("Tank Aiming Compoent"));
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(TEXT("Tank Movement Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimingLog(HitLocation,LaunchSpeed);
}

void ATank::SetComponentDelegates(UBarrelComponent * Barrel,UTankTurretComponent* Turret)
{
	TankAimingComponent->BarrelSetter(Barrel);
	TankAimingComponent->TurretSetter(Turret);
	TankBarrel = Barrel;
}

void ATank::Fire()
{
	if (!TankBarrel)
		{
			return;
		}
	bool isReloaded = (FPlatformTime::Seconds() - LastLaunchTime) > ReloadTime;
	if (isReloaded)
	{
		AProjectile* LaunchedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, TankBarrel->GetSocketLocation(FName("Projectile")), TankBarrel->GetSocketRotation(FName("Projectile")));
		LaunchedProjectile->LaunchProjectile(LaunchSpeed);
		LastLaunchTime = FPlatformTime::Seconds();
	}

}




