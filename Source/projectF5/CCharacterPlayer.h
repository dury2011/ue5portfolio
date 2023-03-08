#pragma once

#include "CoreMinimal.h"
#include "CCharacter.h"
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
	FName _RifleHolsterSocketName;

	UPROPERTY(EditDefaultsOnly)
	FName _RifleEquipHipSocketName;
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
protected:
	virtual void Action() override final;
	virtual void BeginPlay() override;
};