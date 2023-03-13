#include "CProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACProjectile::ACProjectile()
{
 	PrimaryActorTick.bCanEverTick = false;
	_ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileComponent");
}

void ACProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACProjectile::SetProjectileLifeSpan(float InLifeSpan)
{
	SetLifeSpan(InLifeSpan);
}

void ACProjectile::ShootProjectileToCrosshairDirection(const FVector& InDirection)
{
	_ProjectileComponent->Velocity = InDirection * _ProjectileComponent->InitialSpeed;
}