#pragma once

#include "CoreMinimal.h"
#include "CWeapon.h"
#include "Components/TimelineComponent.h"
#include "CWeaponGun.generated.h"

UENUM(BlueprintType)
enum class EWeaponGunFireSelectorType : uint8
{
	SemiAuto = 0, FullAuto, Max
};

UENUM(BlueprintType)
enum class EWeaponGunStateType : uint8
{
	Idle = 0, Fire, Max
};

UENUM(BlueprintType)
enum class EWeaponGunAmmoCountType : uint8
{
	OutAmmo = 0, FullAmmo, Max
};

// 타임라인을 사용한 반동 구현이 커브를 사용하므로 Randomfloat보다 좀 더 정밀한 반동 구현이 가능한 것 같음. 
// https://www.youtube.com/watch?v=3Iyf5whKWWI&list=PLfCrVJxHeD5Yjegzox9g_9oFK5OH6YRRo&index=4
USTRUCT(BlueprintType)
struct FRecoilTimeline
{
	GENERATED_BODY()
	
	UPROPERTY()
	FTimeline RecoilTimeline;

	UPROPERTY(EditDefaultsOnly)
	class UCurveVector* RecoilCurve;

	UPROPERTY(EditDefaultsOnly)
	float RecoilSpeed = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	float RecoilRecoverSpeed = 15.0f;
	
	UPROPERTY()
	FVector InterpVector;
};

UCLASS()
class PROJECTF5_API ACWeaponGun : public ACWeapon
{
	GENERATED_BODY()
// ******************************************************************************************************
// properties
// ******************************************************************************************************
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName _MuzzleSocketName = FName("MuzzleFlash_Socket");

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName _ChamberSocketName = FName("BulletShell_Socket");

	UPROPERTY(EditDefaultsOnly)
	FName _ADSSocketName = FName("AimSocket");

	struct WeaponGunInfo
	{
		
		UPROPERTY()
		EWeaponGunFireSelectorType FireSelectorType = EWeaponGunFireSelectorType::FullAuto;
		UPROPERTY()
		EWeaponGunStateType GunStateType = EWeaponGunStateType::Idle;
		UPROPERTY()
		EWeaponGunAmmoCountType GunAmmoCountType = EWeaponGunAmmoCountType::FullAmmo;
		UPROPERTY()
		bool BFiring = false;

	}_WeaponGunInfo;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACProjectile> _ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* _WeaponFireAnimMontage;

	UPROPERTY(EditDefaultsOnly)
	uint8 _FullAmmo = 30;

	UPROPERTY(EditDefaultsOnly)
	float _FullAutoFiringInterval = 0.2f;

	UPROPERTY(EditDefaultsOnly)
	float _ShootProjectileCameraLength = 50.0f;
	
	UPROPERTY(EditDefaultsOnly)
	FRecoilTimeline _RecoilTimeline;
	
	UPROPERTY()
	class ACProjectile* _Projectile;

	UPROPERTY()
	class ACCharacterPlayer* _OwnerCharacterPlayer;
	
	UPROPERTY()
	class UCameraComponent* _OwnerCamera;

	UPROPERTY()
	FTimerHandle _FullAutoTimerHandle;
	
	UPROPERTY()
	uint8 _LeftAmmo = _FullAmmo;

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
	
	// Bind함수는 반드시 UFUNCTION 메크로 사용해야한다. 
	UFUNCTION()
	void RecoilTimelineUpdateCallback(FVector InVector);

private:
	void FireLogic();
	void RecoilLogic(FVector InVector);
	void RecoilRecoverLogic(FVector InVector);

protected:
	virtual void BeginPlay() override final;

	UFUNCTION(BlueprintImplementableEvent)
	void VFXGunFire();

};