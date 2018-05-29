// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"
class AProjectile;
UENUM()
enum class EAimStatus : uint8
{
	RELOADING,
	AIMING,
	LOCKED
};
class UBarrelComponent;
class UTankTurretComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKZONEGAME_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()
	UBarrelComponent* TankBarrel = nullptr;
	UTankTurretComponent* TankTurret = nullptr;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
	bool isBarrelMoving();
public:
	// Sets default values for this component's properties
	UPROPERTY(BlueprintReadOnly)
		EAimStatus FiringStatus = EAimStatus::RELOADING;
	UAimingComponent();
	void AimingLog(FVector AimLocation);
	UFUNCTION(BlueprintCallable)
	void Initialise(UBarrelComponent* Barrel, UTankTurretComponent* Turret);
	void MoveAimTo(FVector AimTurretto);
	float LaunchSpeed = 8000.f;
	UFUNCTION(BlueprintCallable)
		void Fire();
	UPROPERTY(EditAnywhere)
		float LastLaunchTime = 0.f;
	UPROPERTY(EditAnywhere)
		double ReloadTime = 5;
	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> Projectile;
	FVector AimedAt;
};