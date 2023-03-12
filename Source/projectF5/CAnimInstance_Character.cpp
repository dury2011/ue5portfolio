#include "CAnimInstance_Character.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "CCharacterAnimationinterface.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance_Character::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	_AnimInstanceOwner = Cast<ACharacter>(TryGetPawnOwner());

	if (_AnimInstanceOwner == NULL) return;
	_AnimationInterface = Cast<ICCharacterAnimationinterface>(_AnimInstanceOwner);
}

void UCAnimInstance_Character::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (_AnimInstanceOwner == NULL) return;
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
	{
	_IKRecoil.Recoil = UKismetMathLibrary::TInterpTo(_IKRecoil.Recoil, _IKRecoil.TotalRecoil, DeltaSeconds, 15.0f);
	UE_LOG(LogTemp, Warning, TEXT("IKReCoil.Recoil.Location.X: %f"), _IKRecoil.Recoil.GetLocation().X);
	UE_LOG(LogTemp, Warning, TEXT("IKReCoil.Recoil.Location.X: %f"), _IKRecoil.Recoil.GetLocation().Y);
	UE_LOG(LogTemp, Warning, TEXT("IKReCoil.Recoil.Location.X: %f"), _IKRecoil.Recoil.GetLocation().Z);
	}
	else if (!UKismetMathLibrary::NearlyEqual_TransformTransform(_IKRecoil.Recoil, _IKRecoil.EmptyTransform, 0.005f, 0.005f, 0.005f))
	{
	_IKRecoil.Recoil = UKismetMathLibrary::TInterpTo(_IKRecoil.Recoil, _IKRecoil.EmptyTransform, DeltaSeconds, 7.0f);
	UE_LOG(LogTemp, Warning, TEXT("IKReCoil.Recoil.Location.X: %f"), _IKRecoil.Recoil.GetLocation().X);
	UE_LOG(LogTemp, Warning, TEXT("IKReCoil.Recoil.Location.X: %f"), _IKRecoil.Recoil.GetLocation().Y);
	UE_LOG(LogTemp, Warning, TEXT("IKReCoil.Recoil.Location.X: %f"), _IKRecoil.Recoil.GetLocation().Z);
	}
}

void UCAnimInstance_Character::IKGunFireRecoilStart(FTransform InRecoilTransform)
{
	_IKRecoil.TotalRecoil =_IKRecoil.Recoil * InRecoilTransform;
	_IKRecoil.BApplyRecoil = true;
};

void UCAnimInstance_Character::IKGunFireRecoilEnd()
{
	_IKRecoil.BApplyRecoil = false;
};