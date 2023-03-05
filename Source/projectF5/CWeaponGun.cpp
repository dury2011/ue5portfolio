#include "CWeaponGun.h"
#include "GameFramework/Character.h"
#include "CProjectile.h"

ACWeaponGun::ACWeaponGun()
	: ACWeapon()
{

}

void ACWeaponGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACWeaponGun::BeginPlay()
{
	Super::BeginPlay();
}

void ACWeaponGun::Attack()
{
	Super::Attack();
	
	FActorSpawnParameters _params;
	_params.Owner = this;
	
	// 총의 경우 Muzzle에서 총알이 나가야되는데 Muzzle은 본
	//ACharacter* _weaponGun = Cast<ACharacter>(this);

	// 수정 필요할 수도
	//if (_ProjectileClass && _weaponGun)
		//_Projectile = GetWorld()->SpawnActor<ACProjectile>(_ProjectileClass, _weaponGun->GetMesh()->GetSocketTransform(_SocketName), _params);
	// Projectile은 속도가 빠르므로 굳이 Muzzle에서 나갈 필요가 없을지도? _Owner에서 소캣 만들어서 마찬가지로 무기마다 다르게 발사되도록 해도 될듯?
}