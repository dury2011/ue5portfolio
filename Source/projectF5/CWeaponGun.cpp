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
	
	// ���� ��� Muzzle���� �Ѿ��� �����ߵǴµ� Muzzle�� ��
	//ACharacter* _weaponGun = Cast<ACharacter>(this);

	// ���� �ʿ��� ����
	//if (_ProjectileClass && _weaponGun)
		//_Projectile = GetWorld()->SpawnActor<ACProjectile>(_ProjectileClass, _weaponGun->GetMesh()->GetSocketTransform(_SocketName), _params);
	// Projectile�� �ӵ��� �����Ƿ� ���� Muzzle���� ���� �ʿ䰡 ��������? _Owner���� ��Ĺ ���� ���������� ���⸶�� �ٸ��� �߻�ǵ��� �ص� �ɵ�?
}