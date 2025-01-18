// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MissionPossible/Health/HealthManager.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileSphereComponent"));
	ProjectileCollisionComponent->InitSphereRadius(7.0f);
	RootComponent = ProjectileMesh;

	ProjectileMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ExecuteProjectile();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::ExecuteProjectile()
{
	ProjectileMovementComponent->SetUpdatedComponent(ProjectileMesh);
	ProjectileMovementComponent->InitialSpeed = ProjectileSpeed;
	ProjectileMovementComponent->MaxSpeed = ProjectileSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f; 
	ProjectileMovementComponent->Velocity = ProjectileSpeed * ProjectileMesh->GetForwardVector();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
	OtherActor->GetComponentByClass<UHealthManager>()->ReceiveDamage(DamageAmount);
}


