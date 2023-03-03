#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CIteminterface.generated.h"

UINTERFACE(MinimalAPI)
class UCIteminterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTF5_API ICIteminterface
{
	GENERATED_BODY()

public:
	virtual float ActivateItemAbility() = 0;
};
