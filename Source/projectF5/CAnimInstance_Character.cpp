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
	_CharacterActType = _AnimationInterface->GetCharacterActType();
}