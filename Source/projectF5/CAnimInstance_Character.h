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

	// ����ü ����� ���� CCharacter.h �����ϸ� ���ɻ� ������ ������? 
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	ECharacterActType _CharacterActType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool _BInAir;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool _BAccelerating;

// ******************************************************************************************************************
// methods
// ******************************************************************************************************************
public:

private:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSconds) override;

protected:

};
