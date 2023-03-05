#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectile.generated.h"

UCLASS()
class PROJECTF5_API ACProjectile : public AActor
{
	GENERATED_BODY()
// ******************************************************************************************************
// properties
// ******************************************************************************************************	
public:
private:
	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* _ProjectileComponent;

protected:

// ******************************************************************************************************
// methods
// ******************************************************************************************************

public:	
	ACProjectile();
	virtual void Tick(float DeltaTime) override;
private:

protected:
	virtual void BeginPlay() override;
};
