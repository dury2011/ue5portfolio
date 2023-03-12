#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
//#include "CInGameUMGData.h"
#include "CIngameUMGinterface.generated.h"

UINTERFACE(MinimalAPI)
class UCIngameUMGinterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTF5_API ICIngameUMGinterface
{
	GENERATED_BODY()

public:
	//virtual UCInGameUMGData* GetInGameUMGData() { return NULL; } //???: ±¦ÂúÀº°¡?
};
