// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnSuspensionComponent.h"
#include"Engine/World.h"
#include"Classes/Kismet/GameplayStatics.h"
// Sets default values for this component's properties
USpawnSuspensionComponent::USpawnSuspensionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void USpawnSuspensionComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnedComponent = GetWorld()->SpawnActorDeferred<AActor>(SuspensionSpring,GetComponentTransform());
	
	if (!ensure(SpawnedComponent))
		return;
	SpawnedComponent->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedComponent, GetComponentTransform());
	
}


// Called every frame
void USpawnSuspensionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor*  USpawnSuspensionComponent::ReturnChild()
{
	return SpawnedComponent;
}

