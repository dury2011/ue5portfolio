#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

UCLASS()
class PROJECTF5_API ACWeapon : public AActor
{
	GENERATED_BODY()
// ******************************************************************************************************
// properties
// ******************************************************************************************************
public:
private:
protected:
	UPROPERTY()
	class ACharacter* _Owner;
// ******************************************************************************************************
// methods
// ******************************************************************************************************
public:	
	ACWeapon();
	virtual void Tick(float DeltaTime) override;

private:

protected:
	virtual void BeginPlay() override;
	virtual void Attack(); 
};