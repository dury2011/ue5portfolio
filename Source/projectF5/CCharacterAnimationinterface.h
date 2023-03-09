#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CCharacterAnimationinterface.generated.h"

// Aim 포즈는 필요 없을 듯.
UENUM(BlueprintType)
enum class ECharacterWeaponAnimationType : uint8
{
	UnEquipped = 0, RifleEquipped, PistolEquipped, KnifeEquipped, GreanadeEquipped, Max
};

UINTERFACE(MinimalAPI)
class UCCharacterAnimationinterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTF5_API ICCharacterAnimationinterface
{
	GENERATED_BODY()

public:
	virtual ECharacterWeaponAnimationType GetCharacterWeaponAnimationType() { return ECharacterWeaponAnimationType::Max; }
	virtual float GetGunIdleAnimationPlayRate() { return 0.0f; }
};
