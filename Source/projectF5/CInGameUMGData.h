#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CCharacter.h"
#include "CWeaponGun.h"
#include "CInGameUMGData.generated.h"

UCLASS()
class PROJECTF5_API UCInGameUMGData : public UObject/*, public ICIngameUMGinterface*/
{
	GENERATED_BODY()
// ******************************************************************************************************
// properties
// ******************************************************************************************************
public:
private:
	int32 _Level;
	float _Hp;
	float _Mp;
	float _Sp;
	ECharacterWeaponSlotType _CurrentWeaponSlotType;
	ECharacterWeaponFireSelectorType _CurrentWeaponFireSelectorType;
protected:
// ******************************************************************************************************
// methods
// ******************************************************************************************************
public:
	UCInGameUMGData();
	FORCEINLINE void SetCharacterLv(int32 InLv) { _Level = InLv; }
	FORCEINLINE void SetCharacterHp(float InHp) { _Hp = InHp; }
	FORCEINLINE void SetCharacterMp(float InMp) { _Mp = InMp; }
	FORCEINLINE void SetCharacterSp(float InSp) { _Sp = InSp; }
	FORCEINLINE void SetCurrentWEaponSlotType(ECharacterWeaponSlotType InType) {_CurrentWeaponSlotType = InType; }
	FORCEINLINE void SetCurrentWeaponFireSelectorType(ECharacterWeaponFireSelectorType InType) { _CurrentWeaponFireSelectorType = InType; }
	
	FORCEINLINE int32 GetCharacterLv() { return _Level; }
	FORCEINLINE float GetCharacterHp() { return _Hp; }
	FORCEINLINE float GetCharacterMp() { return _Mp; }
	FORCEINLINE float GetCharacterSp() { return _Sp; }
	FORCEINLINE ECharacterWeaponSlotType GetCurrentWeaponSlotType() { return _CurrentWeaponSlotType; }
	FORCEINLINE ECharacterWeaponFireSelectorType GetCurrentWeaponFireSelectorType() { return _CurrentWeaponFireSelectorType; }

	FORCEINLINE UCInGameUMGData* GetInGameUMGData() { return this; }

	// ICInGameUMGinterface override
	//virtual UCInGameUMGData* GetInGameUMGData() { return this; }

private:
protected:
};
