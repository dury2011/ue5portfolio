#include "CWeaponGun.h"
#include "GameFramework/Character.h"
#include "CAnimInstance_Character.h"
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

void ACWeaponGun::StartAbility()
{
	Super::StartAbility();
	
	FActorSpawnParameters _params;
	_params.Owner = this;
	_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	switch (_FireSelectorType)
	{
		case ECharacterWeaponFireSelectorType::SemiAuto:
		{
			if (_LeftAmmo <= 0) return;
			if (!_ProjectileClass) return;
			if (!_Owner) return;
			
			_Projectile = GetWorld()->SpawnActor<ACProjectile>(_ProjectileClass, _SkeletalMeshComponent->GetSocketTransform(_MuzzleSocketName), _params);
			_LeftAmmo--;
			Cast<UCAnimInstance_Character>(_Owner->GetMesh()->GetAnimInstance())->IKGunFireRecoilStart(_GunRecoil);
			if(_Projectile)
			_Projectile->SetProjectileLifeSpan(_Projectile->_ProjectileLifeSpan);
			UE_LOG(LogTemp, Warning, TEXT("LeftAmmo: %d"), _LeftAmmo);
			
			break;
		}
		case ECharacterWeaponFireSelectorType::FullAuto:
		{
			// https://bbagwang.com/unreal-engine/%EC%96%B8%EB%A6%AC%EC%96%BC-c%EC%97%90%EC%84%9C-delay%EB%A5%BC-%EC%A2%80%EB%8D%94-%ED%8E%B8%ED%95%98%EA%B2%8C-%EC%93%B0%EA%B3%A0%EC%8B%B6%EB%8B%A4%EB%A9%B4/
			// https://hyo-ue4study.tistory.com/324
			GetWorld()->GetTimerManager().SetTimer(_FullAutoTimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				if (_LeftAmmo <= 0) return;
				if (!_ProjectileClass) return;
				if (!_Owner) return;

				FActorSpawnParameters _params;
				_params.Owner = this;
				_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				_Projectile = GetWorld()->SpawnActor<ACProjectile>(_ProjectileClass, _SkeletalMeshComponent->GetSocketTransform(_MuzzleSocketName), _params);
				_LeftAmmo--;
				Cast<UCAnimInstance_Character>(_Owner->GetMesh()->GetAnimInstance())->IKGunFireRecoilStart(_GunRecoil);
				if (_Projectile)
				_Projectile->SetProjectileLifeSpan(_Projectile->_ProjectileLifeSpan);
				UE_LOG(LogTemp, Warning, TEXT("LeftAmmo: %d"), _LeftAmmo);
				
			}), _FullAutoFiringInterval, true);

			break;
		}
		default:
			break;
	}
}

void ACWeaponGun::EndAbility()
{
	Super::EndAbility();
	
	if (!_Owner) return;

	if (GetWorld()->GetTimerManager().IsTimerActive(_FullAutoTimerHandle))
		GetWorld()->GetTimerManager().ClearTimer(_FullAutoTimerHandle);

	Cast<UCAnimInstance_Character>(_Owner->GetMesh()->GetAnimInstance())->IKGunFireRecoilEnd();
}

void ACWeaponGun::Reload()
{
	_LeftAmmo = _FullAmmo;
}