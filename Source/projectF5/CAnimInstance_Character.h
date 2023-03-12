#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CCharacter.h"
#include "CAnimInstance_Character.generated.h"

USTRUCT(BlueprintType)
struct FIKRecoil
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool BApplyRecoil = true;

	UPROPERTY(BlueprintReadOnly)
	FTransform Recoil;

	UPROPERTY(BlueprintReadOnly)
	FTransform TotalRecoil;

	UPROPERTY(BlueprintReadOnly)
	FTransform EmptyTransform {FRotator::ZeroRotator, FVector3d::ZeroVector, FVector3d(1.0f, 1.0f, 1.0f) };
};

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

	class ICCharacterAnimationinterface* _AnimationInterface;

protected:
	UPROPERTY(BlueprintReadOnly)
	float _Speed;

	UPROPERTY(BlueprintReadOnly)
	float _Yaw;

	UPROPERTY(BlueprintReadOnly)
	float _Pitch;

	UPROPERTY(BlueprintReadOnly)
	float _Roll;

	UPROPERTY(BlueprintReadOnly)
	float _Direction;

	UPROPERTY(BlueprintReadOnly)
	bool _BInAir;

	UPROPERTY(BlueprintReadOnly)
	bool _BAccelerating;

	UPROPERTY(BlueprintReadOnly)
	float _GunIdlePlayRate = 1.0f;

	UPROPERTY(BlueprintReadOnly)
	ECharacterWeaponAnimationType _WeaponAnimationType;

	// IKº» º¯°æ
	UPROPERTY(BlueprintReadOnly)
	FIKRecoil _IKRecoil;

// ******************************************************************************************************************
// methods
// ******************************************************************************************************************
public:
	void IKGunFireRecoilStart(FTransform InRecoilTransform);
	void IKGunFireRecoilEnd();
private:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSconds) override;

protected:

};
