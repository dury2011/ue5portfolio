#include "CItem.h"
#include "Components/SphereComponent.h"
//#include "projectF5.h"

ACItem::ACItem()
	:_ItemType(EItemType::Max), _BuffFloatValue(150.0f)
{
	PrimaryActorTick.bCanEverTick = false;
	_SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
}

void ACItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ACItem::ActivateItemAbility()
{
	UE_LOG(LogTemp, Warning, TEXT("Function Called: %s"), *FString("ACItem::ActivateItemAbility()"));
	if (_ItemType == EItemType::Hp || _ItemType == EItemType::Mp || _ItemType == EItemType::Sp) return _BuffFloatValue;
	else return 0.0f;
}

void ACItem::BeginPlay()
{
	Super::BeginPlay();
}



