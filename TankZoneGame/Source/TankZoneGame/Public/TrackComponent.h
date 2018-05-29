// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TrackComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKZONEGAME_API UTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
		UTrackComponent();
	void ApplySidewaysForce();
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);
	void Accelerate();
	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 40000.f;
	float CurrentThrottle = 0;
};
