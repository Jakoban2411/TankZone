// Fill out your copyright notice in the Description page of Project Settings.

#include "SuspensionWheel.h"
#include"Components/StaticMeshComponent.h"
#include"PhysicsEngine/PhysicsConstraintComponent.h"
#include"Classes/Components/SphereComponent.h"

// Sets default values
ASuspensionWheel::ASuspensionWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	SuspensionPhysics = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Suspension Spring"));
	AxlePhysics = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Physics"));
	Wheel=CreateDefaultSubobject<USphereComponent>(FName("Track"));
	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle Mesh"));

	SetRootComponent(SuspensionPhysics);
	Axle->SetupAttachment(SuspensionPhysics);
	Wheel->SetupAttachment(Axle);
	AxlePhysics->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASuspensionWheel::BeginPlay()
{
	Super::BeginPlay();
	
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASuspensionWheel::OnHit);
	ConstraintAttach();
}

void ASuspensionWheel::ConstraintAttach()
{
	auto Root = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (Root)
	{
		SuspensionPhysics->SetConstrainedComponents(Root, NAME_None, Axle, NAME_None);
		AxlePhysics->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
	}
}

// Called every frame
void ASuspensionWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentThrottle = 0.f;

}

void ASuspensionWheel::AddDrivingForce(float Throttle)
{	
	CurrentThrottle += Throttle;
	
}

void ASuspensionWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	Wheel->AddForce(CurrentThrottle*MaxDrivingForce*Axle->GetForwardVector());
}

