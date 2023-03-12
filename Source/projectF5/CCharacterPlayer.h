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
private:
	UPROPERTY(EditDefaultsOnly)
	FName _RifleHolsterSocketName = FName("RifleHolster");

	UPROPERTY(EditDefaultsOnly)
	FName _RifleEquipSocketName = FName("RifleEquip");

	UPROPERTY(EditDefaultsOnly)
	FName _ADSSocketName = FName("ADS");

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
// ******************************************************************************************************
public:
	ACCharacterPlayer();
	virtual void Tick(float DeltaTime) override final;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override final;

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
	virtual void BeginPlay() override final;
};