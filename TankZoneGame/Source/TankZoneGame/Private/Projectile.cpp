// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include"Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include"Classes/PhysicsEngine/RadialForceComponent.h"
#include"Engine/World.h"
#include"Runtime/Engine/Public/TimerManager.h"
#include"Runtime/Engine/Classes/Kismet/GameplayStatics.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Projectile Mesh Component"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	RadialForce= CreateDefaultSubobject<URadialForceComponent>(FName("Radial Force"));

	ImpactBlast->bAutoActivate = false;
	ProjectileMovement->bAutoActivate = false;
	
	LaunchBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
	RadialForce->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement->bShouldBounce = true;
	CollisionMesh->SetVisibility(false);
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::ProjectileHit);
}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector*LaunchSpeed);
	ProjectileMovement->Activate();
}

void AProjectile::ProjectileHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	RadialForce->FireImpulse();
	FTimerHandle TimeHandle;
	GetWorld()->GetTimerManager().SetTimer(TimeHandle, this, &AProjectile::OnTimerExpire, DestroyDelay);
	UGameplayStatics::ApplyRadialDamage(this, Damage, GetActorLocation(), RadialForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}
