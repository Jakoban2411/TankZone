// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnSuspensionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKZONEGAME_API USpawnSuspensionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnSuspensionComponent();
	AActor* ReturnChild();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor>SuspensionSpring;	
	
	UPROPERTY()
		AActor* SpawnedComponent;
};
