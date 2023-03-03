#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CIteminterface.h"
#include "CItem.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Hp, Mp, Sp, Max
};

UCLASS()
class PROJECTF5_API ACItem : public AActor, public ICIteminterface
{
	GENERATED_BODY()
// ******************************************************************************************************
// properties
// ******************************************************************************************************
public:

private:
	// 아이템 종류
	UPROPERTY(EditDefaultsOnly)
	EItemType _ItemType = EItemType::Max;

	// 수치 버프 값
	UPROPERTY(EditDefaultsOnly)
	float _BuffFloatValue;

protected:
// ******************************************************************************************************
// methods
// ******************************************************************************************************
public:	
	ACItem();
	virtual void Tick(float DeltaTime) override;
	virtual float ActivateItemAbility() override;

private:

protected:
	virtual void BeginPlay() override;
};
