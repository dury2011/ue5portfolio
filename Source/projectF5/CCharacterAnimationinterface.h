#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CCharacterAnimationinterface.generated.h"

UENUM(BlueprintType)
enum class ECharacterActType : uint8
{
	Idle, Pistol, Rifle, Onehand, Twohand, Granade, Item, Max
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
	virtual ECharacterActType GetCharacterActType() { return ECharacterActType::Max; }
};
