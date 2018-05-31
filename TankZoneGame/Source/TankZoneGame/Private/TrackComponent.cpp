// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackComponent.h"
#include"Engine/World.h"
UTrackComponent::UTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTrackComponent::ApplySidewaysForce()
{
	float Slippage = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectionVector = (-Slippage / DeltaTime) * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass()*CorrectionVector) / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTrackComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this,&UTrackComponent::OnHit);
}

void UTrackComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Accelerate();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTrackComponent::SetThrottle(float Throttle)
{
	//CurrentThrottle += Throttle;
	CurrentThrottle=FMath::Clamp<float>(CurrentThrottle + Throttle, -3, 3);
	//Accelerate();
	//CurrentThrottle = 0;
}


void UTrackComponent::Accelerate()
{
	FVector ForceApplied = GetForwardVector()*CurrentThrottle*MaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}