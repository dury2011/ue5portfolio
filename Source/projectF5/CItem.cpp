#include "CItem.h"

ACItem::ACItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ACItem::ActivateItemAbility()
{
	if (_ItemType == EItemType::Hp || _ItemType == EItemType::Mp || _ItemType == EItemType::Sp)
		return _BuffFloatValue;
	else return 0.0f;
}

void ACItem::BeginPlay()
{
	Super::BeginPlay();
}



