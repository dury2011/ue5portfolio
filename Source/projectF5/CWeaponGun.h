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
	// ���⸶�� ���� ��ġ�� �ٸ��Ƿ� �̸� �ʿ�
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
