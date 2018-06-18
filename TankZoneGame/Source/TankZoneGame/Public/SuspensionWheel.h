// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SuspensionWheel.generated.h"
class USphereComponent;
class UPhysicsConstraintComponent;
UCLASS()
class TANKZONEGAME_API ASuspensionWheel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASuspensionWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ConstraintAttach();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* SuspensionPhysics = nullptr;
	UPROPERTY(VisibleAnywhere)
		UPhysicsConstraintComponent* AxlePhysics = nullptr;
	UPROPERTY(VisibleAnywhere)
		USphereComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere)
		USphereComponent* Axle = nullptr;
	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 500000.f;
	void AddDrivingForce(float Throttle);
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	float CurrentThrottle=0.f;
};
