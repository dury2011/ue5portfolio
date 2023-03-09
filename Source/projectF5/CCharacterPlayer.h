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

	// https://unrealcommunity.wiki/timeline-in-cpp-1uktygtd Âü°í
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
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void Rifle();
	void Pistol();
	void Knife();
	void Grenade();
	void OnAim();
	void OffAim();
	void AimTimelineUpdateCallback(float InterpValue);
protected:
	virtual void Action() override final;
	virtual void BeginPlay() override;
};