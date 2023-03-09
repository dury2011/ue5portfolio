#pragma once

#include "CoreMinimal.h"
#include "CWeapon.h"
#include "CWeaponGun.generated.h"

UCLASS()
class PROJECTF5_API ACWeaponGun : public ACWeapon
{
	GENERATED_BODY()
// ******************************************************************************************************
// properties
// ******************************************************************************************************
public:
	// 무기마다 소켓 위치가 다르므로 이름 필요
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName _MuzzleSocketName;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACProjectile> _ProjectileClass;



	UPROPERTY()
	class ACProjectile* _Projectile;

protected:
// ******************************************************************************************************
// methods
// ******************************************************************************************************
public:
	ACWeaponGun();
	virtual void Tick(float DeltaTime) override final;

private:

protected:
	virtual void BeginPlay() override final;
	virtual void Attack() override final;
};
