#include "CAnimInstance_Character.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

void UCAnimInstance_Character::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	_AnimInstanceOwner = Cast<ACharacter>(TryGetPawnOwner());

	if (_AnimInstanceOwner == NULL) return;
}

void UCAnimInstance_Character::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (_AnimInstanceOwner == NULL) return;

	_Speed = _AnimInstanceOwner->GetVelocity().Size2D();
	_Yaw = UKismetMathLibrary::NormalizedDeltaRotator(_AnimInstanceOwner->GetBaseAimRotation(), _AnimInstanceOwner->GetActorRotation()).Yaw;
	_Pitch = UKismetMathLibrary::NormalizedDeltaRotator(_AnimInstanceOwner->GetBaseAimRotation(), _AnimInstanceOwner->GetActorRotation()).Pitch;
	_Roll = UKismetMathLibrary::NormalizedDeltaRotator(_AnimInstanceOwner->GetBaseAimRotation(), _AnimInstanceOwner->GetActorRotation()).Roll;
}
