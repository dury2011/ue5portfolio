#pragma once

#include "CoreMinimal.h"
#include "CCharacter.h"
#include "Components/TimelineComponent.h"
#include "CCharacterPlayer.generated.h"

UCLASS()
class PROJECTF5_API ACCharacterPlayer : public ACCharacter
{
	GENERATED_BODY()

// ******************************************************************************************************
// properties
// ******************************************************************************************************
public:
	UPROPERTY(EditDefaultsOnly)
	FName _IKHandGunSocketName = FName("ik_hand_gun");

	UPROPERTY(EditDefaultsOnly)
	FName _IKHandRootSocketName = FName("ik_hand_root");
private:
	UPROPERTY(EditDefaultsOnly)
	FName _RifleHolsterSocketName = FName("RifleHolster");

	UPROPERTY(EditDefaultsOnly)
	FName _RifleEquipSocketName = FName("RifleEquip");

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* _WeaponRifleFireAnimMontage;

	UPROPERTY()
	class UCInGameUMGData* _InGameUMGData;

	// https://unrealcommunity.wiki/timeline-in-cpp-1uktygtd
	struct AimTimeline
	{
		UPROPERTY()
		class UTimelineComponent* AimTimeline;

		UPROPERTY()
		class UCurveFloat* AimCurve;

		FOnTimelineFloat OnAimTimelineCallback;

		float InterpFloat = 0.0f;
	} _AimTimeline;

protected:
// ******************************************************************************************************
// methods
// ******************************************************************************************************ssss
public:
	ACCharacterPlayer();
	virtual void Tick(float DeltaTime) override final;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override final;
	FORCEINLINE UAnimMontage* GetRifleFireAnimMontage() { return _WeaponRifleFireAnimMontage; }

private:
	void Rifle();
	void Pistol();
	void Knife();
	void Grenade();
	void OnAim();
	void OffAim();
	void FireSelect();
	void Reload();
	void AimTimelineUpdateCallback(float InterpValue);

protected:
	virtual void OnAction() override final;
	virtual void OffAction() override final;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override final;
	// virtual void ReceivePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser) override final;
	virtual void BeginPlay() override final;
};