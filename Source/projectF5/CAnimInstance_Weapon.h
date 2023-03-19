#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance_Weapon.generated.h"

UCLASS()
class PROJECTF5_API UCAnimInstance_Weapon : public UAnimInstance
{
	GENERATED_BODY()
// ******************************************************************************************************************
// properties
// ******************************************************************************************************************
public:
private:
protected:
// ******************************************************************************************************************
// methods
// ******************************************************************************************************************
public:
private:
private:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSconds) override;
};