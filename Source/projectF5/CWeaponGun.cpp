#include "CWeaponGun.h"
#include "GameFramework/Character.h"
#include "CAnimInstance_Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "CProjectile.h"
#include "Camera/CameraComponent.h"
#include "CCharacterPlayer.h"

void ACWeaponGun::RecoilTimelineUpdateCallback(FVector InVector)
{
	if (_WeaponGunInfo.BFiring)
		RecoilLogic(InVector);
	else
		RecoilRecoverLogic(InVector);
}

ACWeaponGun::ACWeaponGun()
	: ACWeapon()
{

}

void ACWeaponGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_RecoilTimeline.RecoilTimeline.TickTimeline(DeltaTime);
}

void ACWeaponGun::BeginPlay()
{
	Super::BeginPlay();

	if (_Owner)
	{
		_OwnerCamera = Cast<ACCharacter>(_Owner)->GetCameraComponent();
		_OwnerCharacterPlayer = Cast<ACCharacterPlayer>(_Owner);
	}
	if (_RecoilTimeline.RecoilCurve)
	{
		FOnTimelineVector _onFullAutoRecoilTimelineCallback;
		
		_onFullAutoRecoilTimelineCallback.BindUFunction(this, FName("RecoilTimelineUpdateCallback"));
		_RecoilTimeline.RecoilTimeline.AddInterpVector(_RecoilTimeline.RecoilCurve, _onFullAutoRecoilTimelineCallback);
		_RecoilTimeline.RecoilTimeline.SetPropertySetObject(this);
		_RecoilTimeline.RecoilTimeline.SetTimelineLength(5.0f);
	}
}

void ACWeaponGun::StartAbility()
{
	Super::StartAbility();
	
	_WeaponGunInfo.BFiring = true;
	
	switch (_WeaponGunInfo.FireSelectorType)
	{
		case EWeaponGunFireSelectorType::SemiAuto:
		{
			FireLogic();
			break;
		}
		case EWeaponGunFireSelectorType::FullAuto:
		{
			GetWorld()->GetTimerManager().SetTimer(_FullAutoTimerHandle, this, &ACWeaponGun::FireLogic, _FullAutoFiringInterval, true);
			break;
		}
		default:
			break;
	}

	_RecoilTimeline.RecoilTimeline.SetPlayRate(_RecoilTimeline.RecoilSpeed);
	_RecoilTimeline.RecoilTimeline.Play();
}

void ACWeaponGun::EndAbility()
{
	Super::EndAbility();
	
	_WeaponGunInfo.BFiring = false;

	_RecoilTimeline.RecoilTimeline.SetPlayRate(_RecoilTimeline.RecoilRecoverSpeed);
	_RecoilTimeline.RecoilTimeline.Reverse();

	//switch (_WeaponGunInfo.FireSelectorType)
	//{
	//	case EWeaponGunFireSelectorType::SemiAuto:
	//	{
	//		break;
	//	}
	//	case EWeaponGunFireSelectorType::FullAuto:
	//	{	
			if (GetWorld()->GetTimerManager().IsTimerActive(_FullAutoTimerHandle))
			GetWorld()->GetTimerManager().ClearTimer(_FullAutoTimerHandle);

	//		break;
	//	}
	//	default:
	//		break;
	//}
}

void ACWeaponGun::Reload()
{
	_LeftAmmo = _FullAmmo;
}

// https://bbagwang.com/unreal-engine/%EC%96%B8%EB%A6%AC%EC%96%BC-c%EC%97%90%EC%84%9C-delay%EB%A5%BC-%EC%A2%80%EB%8D%94-%ED%8E%B8%ED%95%98%EA%B2%8C-%EC%93%B0%EA%B3%A0%EC%8B%B6%EB%8B%A4%EB%A9%B4/
// https://hyo-ue4study.tistory.com/324
void ACWeaponGun::FireLogic()
{
	// 예외처리
	{
		if (!_ProjectileClass) return;
		if (!_Owner) return;
		if (!_OwnerCharacterPlayer) return;
		if (!_OwnerCamera) return;
		if (_LeftAmmo <= 0) 
		{ 
			_WeaponGunInfo.BFiring = false; 
			
			_RecoilTimeline.RecoilTimeline.SetPlayRate(_RecoilTimeline.RecoilRecoverSpeed);
			_RecoilTimeline.RecoilTimeline.Reverse();

			if (GetWorld()->GetTimerManager().IsTimerActive(_FullAutoTimerHandle))
				GetWorld()->GetTimerManager().ClearTimer(_FullAutoTimerHandle);

			return;
		}
	}

	// Set FireRecoil
	//_GunRecoilInput.BRecoil = true;
	//_GunRecoilInput.TotalRecoil = _GunRecoilInput.Recoil * _GunRecoilInput.MakeRandomRecoilInputTransform();

	// Play Montage
	if (_WeaponFireAnimMontage && _OwnerCharacterPlayer->GetRifleFireAnimMontage())
	{
		_OwnerCharacterPlayer->GetMesh()->GetAnimInstance()->Montage_Play(_OwnerCharacterPlayer->GetRifleFireAnimMontage());
		_SkeletalMeshComponent->GetAnimInstance()->Montage_Play(_WeaponFireAnimMontage);
	}

	// Spawn Projectile
	{
		FActorSpawnParameters _params;
		_params.Owner = this;
		_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		FTransform _camTrans = _OwnerCamera->GetComponentTransform();
		FVector _shootLoc = _camTrans.GetLocation() + FQuat(_camTrans.GetRotation()).GetForwardVector() * _ShootProjectileCameraLength;
		FTransform _shootTrans = UKismetMathLibrary::MakeTransform(_shootLoc, FRotator(_camTrans.GetRotation()));

		_Projectile = GetWorld()->SpawnActor<ACProjectile>(_ProjectileClass, _shootTrans/*_SkeletalMeshComponent->GetSocketTransform(_MuzzleSocketName)*/, _params);
		
		// Set Projectile Direction And LifeSpan
		if (_Projectile)
		{
			_Projectile->SetOwner(_Owner);
			FTransform _ownerCamTrans = _OwnerCamera->GetComponentTransform();
			// 해보고 수정하던지 하기
			_Projectile->ShootProjectileToCrosshairDirection(_OwnerCamera->GetForwardVector());
			_LeftAmmo--;
			UE_LOG(LogTemp, Warning, TEXT("LeftAmmo: %d"), _LeftAmmo);
		}
	}

	// VFX Gun Fire
	VFXGunFire();
}

void ACWeaponGun::RecoilLogic(FVector InVector)
{
	_RecoilTimeline.InterpVector = InVector * _RecoilTimeline.RecoilSpeed;
	_Owner->AddControllerRollInput(_RecoilTimeline.InterpVector.X);
	_Owner->AddControllerPitchInput(_RecoilTimeline.InterpVector.Y);
	_Owner->AddControllerYawInput(_RecoilTimeline.InterpVector.Z);
}

void ACWeaponGun::RecoilRecoverLogic(FVector InVector)
{
	_RecoilTimeline.InterpVector = InVector * -(_RecoilTimeline.RecoilRecoverSpeed);
	_Owner->AddControllerRollInput(_RecoilTimeline.InterpVector.X);
	_Owner->AddControllerPitchInput(_RecoilTimeline.InterpVector.Y);
	//_Owner->AddControllerYawInput(_RecoilTimeline.InterpVector.Z);
}
