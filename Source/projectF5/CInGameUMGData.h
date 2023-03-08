#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CInGameUMGData.generated.h"

UCLASS()
class PROJECTF5_API UCInGameUMGData : public UObject
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
protected:
// ******************************************************************************************************
// methods
// ******************************************************************************************************
public:
	UCInGameUMGData();
	void SetCharacterLv(int32 InLv);
	void SetCharacterHp(float InHp);
	void SetCharacterMp(float InMp);
	void SetCharacterSp(float InSp);

	int32 GetCharacterLv();
	float GetCharacterHp();
	float GetCharacterMp();
	float GetCharacterSp();
private:
protected:
};
