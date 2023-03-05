#include "CWeapon.h"
#include "GameFramework/Character.h"

ACWeapon::ACWeapon()
{
 	PrimaryActorTick.bCanEverTick = false;

}

void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetOwner()) _Owner = Cast<ACharacter>(GetOwner());
}

void ACWeapon::Attack()
{

}