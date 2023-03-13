#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CCharacter.h"
#include "CAnimInstance_Character.generated.h"

USTRUCT(BlueprintType)
struct FIKRecoil
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	bool BApplyRecoil = false;

	UPROPERTY(BlueprintReadOnly)
	FTransform Recoil;

	UPROPERTY()
	FTransform TotalRecoil;

	UPROPERTY()
	FTransform EmptyTransform;

	void IKGunFireRecoilStart(FTransform InRecoilTransform);
	void IKGunFireRecoilEnd();
	bool GetBApplyRecoil() { return BApplyRecoil; }
};

USTRUCT(BlueprintType)
struct FIKAim
{
	GENERATED_BODY()
public:
	UPROPERTY()
	class ACharacter* Aimer;

	UPROPERTY(BlueprintReadOnly)
	FVector AimSocketLocation;

	UPROPERTY(BlueprintReadOnly)
	FRotator AimSocketRotation;

	UPROPERTY(BlueprintReadOnly)
	FVector AimPointLocation;

	//https://www.youtube.com/watch?v=9PJ_-8ZuWsc&list=PLzykqv-wgIQXz6qLDE-wswVJ7pEH9ziKx&index=9
	void SetAimSocket(FName InIKHandSocketName, FName InWeaponAimSocketName);
	void SetAimPoint(FName InIKHandRootName);
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

	// 무기 반동으로 인한 IK본 변경
	UPROPERTY(BlueprintReadOnly)
	FIKRecoil _IKRecoil;

	// 무기 aim으로 인한 IK 본 변경
	UPROPERTY(BlueprintReadOnly)
	FIKAim _IKAim;

// ******************************************************************************************************************
// methods
// ******************************************************************************************************************
public:
	FORCEINLINE FIKAim& GetIKAim() { return _IKAim; }
	FORCEINLINE FIKRecoil& GetIKRecoil() { return _IKRecoil; }

private:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSconds) override;

protected:

};
