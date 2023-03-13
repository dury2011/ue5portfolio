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

USTRUCT(BlueprintType)
struct FRecoilInput
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, Category = "Max Rotation")
	float MinRecoilRollInput = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Max Rotation")
	float MaxRecoilRollInput = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Min Rotation")
	float MinRecoilYawInput = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Max Rotation")
	float MaxRecoilYawInput = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Min Rotation")
	float MinRecoilPitchInput = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Max Rotation")
	float MaxRecoilPitchInput = 0.0f;

public:
	FTransform MakeRandomRecoilInputTransform();
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

	UPROPERTY(EditDefaultsOnly)
	FName _ADSSocketName = FName("AimSocket");
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACProjectile> _ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* _WeaponFireAnimMontage;
	
	UPROPERTY(EditDefaultsOnly)
	float _BulletFirePosition = 50.0f;

	UPROPERTY(EditDefaultsOnly)
	uint8 _FullAmmo = 30;

	UPROPERTY(EditDefaultsOnly)
	float _FullAutoFiringInterval = 0.2f;
	UPROPERTY()
	class ACProjectile* _Projectile;
	
	UPROPERTY()
	class UCameraComponent* _OwnerCamera;

	UPROPERTY()
	class ACCharacterPlayer* _OwnerCharacterPlayer;

	//https://www.youtube.com/watch?v=wW8MjEfsZ78&list=PLzykqv-wgIQXz6qLDE-wswVJ7pEH9ziKx&index=11
	UPROPERTY(EditDefaultsOnly)
	FRecoilInput _GunRecoilInput;

	UPROPERTY()
	FTimerHandle _FullAutoTimerHandle;
	
	UPROPERTY()
	uint8 _LeftAmmo = _FullAmmo;

	struct ProjectileRecoil
	{
		bool BRecoil = false;
		FTransform Recoil;
		FTransform TotalRecoil;
	} _ProjectileRecoil;
	
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
	void FireLogic();
	void RecoilLogic();
	//void ProjectileGunFireRecoil(FTransform InRecoilTransform);

protected:
	virtual void BeginPlay() override final;

	UFUNCTION(BlueprintImplementableEvent)
	void VFXGunFire();
};