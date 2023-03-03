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
	// ������ ����
	UPROPERTY(EditDefaultsOnly)
	EItemType _ItemType = EItemType::Max;

	// ��ġ ���� ��
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
