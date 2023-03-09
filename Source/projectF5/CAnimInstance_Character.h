#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CCharacter.h"
#include "CAnimInstance_Character.generated.h"

UCLASS()
class PROJECTF5_API UCAnimInstance_Character : public UAnimInstance
{
	GENERATED_BODY()
// ******************************************************************************************************************
// properties
// ******************************************************************************************************************
public:

private:
	UPROPERTY()
	class ACharacter* _AnimInstanceOwner;

	//UPROPERTY()
	class ICCharacterAnimationinterface* _AnimationInterface;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float _Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float _Yaw;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float _Pitch;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float _Roll;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float _Direction;

	// 열거체 사용을 위해 CCharacter.h 포함하면 성능상에 문제가 있을까? 
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	ECharacterWeaponAnimationType _WeaponAnimationType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool _BInAir;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool _BAccelerating;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float _GunIdlePlayRate = 1.0f;

// ******************************************************************************************************************
// methods
// ******************************************************************************************************************
public:

private:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSconds) override;

protected:

};
