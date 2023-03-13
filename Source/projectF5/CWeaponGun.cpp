#include "CWeaponGun.h"
#include "GameFramework/Character.h"
#include "CAnimInstance_Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "CProjectile.h"
#include "Camera/CameraComponent.h"
#include "CCharacterPlayer.h"

FTransform FRecoilInput::MakeRandomRecoilInputTransform()
{
	float _randPitch = UKismetMathLibrary::RandomFloatInRange(MinRecoilPitchInput, MaxRecoilPitchInput);
	float _randYaw = UKismetMathLibrary::RandomFloatInRange(MinRecoilYawInput, MaxRecoilYawInput);
	float _randRoll = UKismetMathLibrary::RandomFloatInRange(MinRecoilRollInput, MaxRecoilRollInput);
	
	return UKismetMathLibrary::MakeTransform(FVector(0.0f, 0.0f, 0.0f), FRotator(_randPitch, _randYaw, _randRoll));
}

ACWeaponGun::ACWeaponGun()
	: ACWeapon()
{

}

void ACWeaponGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RecoilLogic();
}

void ACWeaponGun::BeginPlay()
{
	Super::BeginPlay();

	if (_Owner)
	{
		_OwnerCamera = Cast<ACCharacter>(_Owner)->GetCameraComponent();
		_OwnerCharacterPlayer = Cast<ACCharacterPlayer>(_Owner);
	}
}

void ACWeaponGun::StartAbility()
{
	Super::StartAbility();
	
	if (_LeftAmmo <= 0) return;

	switch (_FireSelectorType)
	{
		case ECharacterWeaponFireSelectorType::SemiAuto:
		{
			FireLogic();
			break;
		}
		case ECharacterWeaponFireSelectorType::FullAuto:
		{
			GetWorld()->GetTimerManager().SetTimer(_FullAutoTimerHandle, this, &ACWeaponGun::FireLogic, _FullAutoFiringInterval, true);
			break;
		}
		default:
			break;
	}
}

void ACWeaponGun::EndAbility()
{
	Super::EndAbility();
	
	_ProjectileRecoil.BRecoil = false;
	_ProjectileRecoil.TotalRecoil = UKismetMathLibrary::MakeTransform(FVector::ZeroVector, FRotator::ZeroRotator);
	_ProjectileRecoil.Recoil = UKismetMathLibrary::MakeTransform(FVector::ZeroVector, FRotator::ZeroRotator);

	if (GetWorld()->GetTimerManager().IsTimerActive(_FullAutoTimerHandle))
	GetWorld()->GetTimerManager().ClearTimer(_FullAutoTimerHandle);
}

void ACWeaponGun::Reload()
{
	_LeftAmmo = _FullAmmo;
}

// https://bbagwang.com/unreal-engine/%EC%96%B8%EB%A6%AC%EC%96%BC-c%EC%97%90%EC%84%9C-delay%EB%A5%BC-%EC%A2%80%EB%8D%94-%ED%8E%B8%ED%95%98%EA%B2%8C-%EC%93%B0%EA%B3%A0%EC%8B%B6%EB%8B%A4%EB%A9%B4/
// https://hyo-ue4study.tistory.com/324
void ACWeaponGun::FireLogic()
{
	if (_LeftAmmo <= 0) return;
	if (!_ProjectileClass) return;
	if (!_Owner) return;
	if (!_OwnerCharacterPlayer) return;
	if (!_OwnerCamera) return;

	_ProjectileRecoil.BRecoil = true;
	_ProjectileRecoil.TotalRecoil = _ProjectileRecoil.Recoil + _GunRecoilInput.MakeRandomRecoilInputTransform();

	FTransform _ownerCamTrans = _OwnerCamera->GetComponentTransform();

	// Play Montage
	if (_WeaponFireAnimMontage && _OwnerCharacterPlayer->GetRifleFireAnimMontage())
	{
		_SkeletalMeshComponent->GetAnimInstance()->Montage_Play(_WeaponFireAnimMontage);
		_OwnerCharacterPlayer->GetMesh()->GetAnimInstance()->Montage_Play(_OwnerCharacterPlayer->GetRifleFireAnimMontage());
	}

	// Spawn Projectile
	FActorSpawnParameters _params;
	_params.Owner = this;
	_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	_Projectile = GetWorld()->SpawnActor<ACProjectile>(_ProjectileClass, _SkeletalMeshComponent->GetSocketTransform(_MuzzleSocketName), _params);
	
	if (_Projectile)
	{
		_Projectile->ShootProjectileToCrosshairDirection(_OwnerCamera->GetForwardVector());
		_Projectile->SetProjectileLifeSpan(_Projectile->_ProjectileLifeSpan);
	}
	
	VFXGunFire();
	
	_LeftAmmo--;

	UE_LOG(LogTemp, Warning, TEXT("LeftAmmo: %d"), _LeftAmmo);
}

void ACWeaponGun::RecoilLogic()
{
	if (_LeftAmmo <= 0) return;
	if (_ProjectileRecoil.BRecoil)
	{
		_ProjectileRecoil.Recoil = UKismetMathLibrary::TInterpTo(_ProjectileRecoil.Recoil, _ProjectileRecoil.TotalRecoil, GetWorld()->GetDeltaSeconds(), 1.0f);
		_Owner->AddControllerPitchInput(_ProjectileRecoil.Recoil.Rotator().Pitch);
		_Owner->AddControllerYawInput(_ProjectileRecoil.Recoil.Rotator().Yaw);
		_Owner->AddControllerRollInput(_ProjectileRecoil.Recoil.Rotator().Roll);
	}
	//else
	//else if (!UKismetMathLibrary::NearlyEqual_TransformTransform(_ProjectileRecoil.Recoil, _ProjectileRecoil.EmptyTransform, 0.005f, 0.005f, 0.005f))
	//{
	//	_ProjectileRecoil.Recoil = UKismetMathLibrary::TInterpTo(_ProjectileRecoil.Recoil, _ProjectileRecoil.EmptyTransform, GetWorld()->GetDeltaSeconds(), 7.0f);
	//	_Owner->AddControllerPitchInput(_ProjectileRecoil.Recoil.Rotator().Pitch);
	//	_Owner->AddControllerYawInput(_ProjectileRecoil.Recoil.Rotator().Yaw);
	//	_Owner->AddControllerRollInput(_ProjectileRecoil.Recoil.Rotator().Roll);
	//}
}