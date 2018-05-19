// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include"Runtime/Engine/Classes/GameFramework/Actor.h"
// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAimingComponent::AimingLog(FVector AimLocation,FString TankName)
{
	if (GetOwner() != nullptr && GetOwner()!=NULL)
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at:%s "),*(GetOwner()->GetName()), *(AimLocation.ToString()));
}

