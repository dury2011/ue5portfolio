#include "CAnimInstance_Character.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "CCharacterAnimationinterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

void FIKRecoil::IKGunFireRecoilStart(FTransform InRecoilTransform)
{
	TotalRecoil = Recoil * InRecoilTransform;
	BApplyRecoil = true;
};

void FIKRecoil::IKGunFireRecoilEnd()
{
	BApplyRecoil = false;
};

void FIKAim::SetAimSocket(FName InIKHandSocketName, FName InWeaponAimSocketName)
{
	ACCharacter* _characterPlayer = Cast<ACCharacter>(Aimer);
	if (_characterPlayer)
	{
		ACWeaponGun* _characterGun = Cast<ACWeaponGun>(_characterPlayer->GetWeapon());
		if (_characterGun)
		{
			FTransform _temp = UKismetMathLibrary::MakeRelativeTransform(_characterGun->GetSkeletalMeshComponent()->GetSocketTransform(InWeaponAimSocketName), _characterPlayer->GetMesh()->GetSocketTransform(InIKHandSocketName));
			AimSocketLocation = _temp.GetLocation();
			AimSocketRotation = FRotator(_temp.GetRotation());
		}
	}
}

void FIKAim::SetAimPoint(FName InIKHandRootName)
{
	ACCharacter* _characterPlayer = Cast<ACCharacter>(Aimer);
	if (_characterPlayer)
	{
		_characterPlayer->GetCameraComponent()->GetComponentTransform();
		FTransform _temp = UKismetMathLibrary::MakeRelativeTransform(_characterPlayer->GetCameraComponent()->GetComponentTransform(), _characterPlayer->GetMesh()->GetSocketTransform(InIKHandRootName));

		AimPointLocation = _temp.GetLocation() + _temp.GetRotation().GetForwardVector() * 20;
	}
}

void UCAnimInstance_Character::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	_AnimInstanceOwner = Cast<ACharacter>(TryGetPawnOwner());

	if (_AnimInstanceOwner == NULL) return;
	_AnimationInterface = Cast<ICCharacterAnimationinterface>(_AnimInstanceOwner);
	_IKAim.Aimer = _AnimInstanceOwner;
}

void UCAnimInstance_Character::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!_AnimInstanceOwner) return;
	_BInAir = _AnimInstanceOwner->GetMovementComponent()->IsFalling();
	_Speed = _AnimInstanceOwner->GetVelocity().Size2D();
	_Yaw = UKismetMathLibrary::NormalizedDeltaRotator(_AnimInstanceOwner->GetBaseAimRotation(), _AnimInstanceOwner->GetActorRotation()).Yaw;
	_Pitch = UKismetMathLibrary::NormalizedDeltaRotator(_AnimInstanceOwner->GetBaseAimRotation(), _AnimInstanceOwner->GetActorRotation()).Pitch;
	_Roll = UKismetMathLibrary::NormalizedDeltaRotator(_AnimInstanceOwner->GetBaseAimRotation(), _AnimInstanceOwner->GetActorRotation()).Roll;
	_Direction = CalculateDirection(_AnimInstanceOwner->GetVelocity(), FRotator(0.0f, _AnimInstanceOwner->GetControlRotation().Yaw, 0.0f));

	if (_AnimInstanceOwner->GetCharacterMovement()->GetCurrentAcceleration().Size2D() > 0.0f) _BAccelerating = true;
	else _BAccelerating = false;

	if (_AnimationInterface == NULL) return;
	_WeaponAnimationType = _AnimationInterface->GetCharacterWeaponAnimationType();
	_GunIdlePlayRate = _AnimationInterface->GetGunIdleAnimationPlayRate();

	if (_IKRecoil.BApplyRecoil)
	_IKRecoil.Recoil = UKismetMathLibrary::TInterpTo(_IKRecoil.Recoil, _IKRecoil.TotalRecoil, DeltaSeconds, 15.0f);
	else if (!UKismetMathLibrary::NearlyEqual_TransformTransform(_IKRecoil.Recoil, _IKRecoil.EmptyTransform, 0.005f, 0.005f, 0.005f))
	_IKRecoil.Recoil = UKismetMathLibrary::TInterpTo(_IKRecoil.Recoil, _IKRecoil.EmptyTransform, DeltaSeconds, 7.0f);
}