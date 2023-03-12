#pragma once

#include "CoreMinimal.h"
#include "CWeapon.h"
//#include "TimerManager.h"
#include "CWeaponGun.generated.h"

UENUM(BlueprintType)
enum class ECharacterWeaponFireSelectorType : uint8
{
	SemiAuto = 0, FullAuto, Max
};

UCLASS()
class PROJECTF5_API ACWeaponGun : public ACWeapon
{
	GENERATED_BODY()
// ******************************************************************************************************
// properties
// ******************************************************************************************************
public:
	UPROPERTY(BlueprintReadOnly)
	ECharacterWeaponFireSelectorType _FireSelectorType = ECharacterWeaponFireSelectorType::FullAuto;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName _MuzzleSocketName;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACProjectile> _ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly)
	uint8 _FullAmmo = 30;

	UPROPERTY()
	uint8 _LeftAmmo = _FullAmmo;

	UPROPERTY(EditDefaultsOnly)
	float _FullAutoFiringInterval = 0.2f;

	UPROPERTY()
	class ACProjectile* _Projectile;

	UPROPERTY()
	FTimerHandle _FullAutoTimerHandle;

	//https://www.youtube.com/watch?v=wW8MjEfsZ78&list=PLzykqv-wgIQXz6qLDE-wswVJ7pEH9ziKx&index=11
	UPROPERTY(EditDefaultsOnly)
	FTransform _GunRecoil;
	
protected:
// ******************************************************************************************************
// methods
// ******************************************************************************************************
public:
	ACWeaponGun();
	virtual void Tick(float DeltaTime) override final;
	virtual void StartAbility() override final;
	virtual void EndAbility() override final;
	void Reload();
	
private:

protected:
	virtual void BeginPlay() override final;
};