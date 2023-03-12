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
	UPROPERTY(EditDefaultsOnly)
	float _ProjectileLifeSpan = 3.0f;

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
	void SetProjectileLifeSpan(float InLifeSpan);
private:

protected:
	virtual void BeginPlay() override;
};
