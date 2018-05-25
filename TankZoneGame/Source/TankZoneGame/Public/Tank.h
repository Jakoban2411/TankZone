// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UAimingComponent;
class UTankMovementComponent;
class UBarrelComponent;
class UTankTurretComponent;
class AProjectile;
UCLASS()
class TANKZONEGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UBarrelComponent* TankBarrel = nullptr;
	UAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;
public:	
	// Called every frame
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable)
	void SetComponentDelegates(UBarrelComponent* Barrel,UTankTurretComponent* Turret);
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000.f;
	UFUNCTION(BlueprintCallable)
		void Fire();
	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> Projectile;
	UPROPERTY(EditAnywhere)
		float LastLaunchTime = 0.f;
	UPROPERTY(EditAnywhere)
		double ReloadTime = 5;
};
