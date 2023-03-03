// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance_Character.generated.h"


/**
 * 
 */
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

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float _Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float _Yaw;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float _Pitch;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float _Roll;

// ******************************************************************************************************************
// methods
// ******************************************************************************************************************
public:

private:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSconds) override;

protected:

};
