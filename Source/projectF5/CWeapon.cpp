#include "CWeapon.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

ACWeapon::ACWeapon()
{
 	PrimaryActorTick.bCanEverTick = false;

	//_CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	//RootComponent = _CapsuleComponent;
	_SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	_SkeletalMeshComponent->SetupAttachment(_CapsuleComponent);
	RootComponent = _SkeletalMeshComponent;
}

void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACWeapon::AttachWeaponUsingObject(class USceneComponent* InAttachComponent, FName InAttachSocketName)
{
	InAttachComponent->AttachToComponent(_SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, InAttachSocketName);
}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetOwner()) _Owner = Cast<ACharacter>(GetOwner());
}

void ACWeapon::Attack()
{

}