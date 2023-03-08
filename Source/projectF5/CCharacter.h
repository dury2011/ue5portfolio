#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacterAnimationinterface.h"
#include "CInGameUMGinterface.h"
#include "CWeaponGun.h"
#include "CCharacter.generated.h"



// Transform 조정은 블루프린트에서 함
UCLASS()
class PROJECTF5_API ACCharacter : public ACharacter, public ICCharacterAnimationinterface, public ICIngameUMGinterface
{
	GENERATED_BODY()
// ******************************************************************************************************
// properties
// ******************************************************************************************************
public:
private:
	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* _CameraComponent;

	UPROPERTY()
	ECharacterActType _ActType;

	UPROPERTY()
	class UCInGameUMGData* _InGameUMGData;

protected:
	// 캐릭터 스탯
	struct Stats
	{
		int32 Level;
		
		float Hp;
		float Mp;
		float Sp;
	} _CharacterStats;

	struct WeaponSlot
	{
		bool BAiming;
		// Aim중에 Idle 애니메이션의 재생을 막아서 애니메이션으로 인한 흔들림 방지
		float GunIdleAnimationPlayRate = 1.0f;
		ECharacterWeaponSlotType CurrentWeaponSlotType = ECharacterWeaponSlotType::Max;
		TArray<class ACWeapon*> Weapons;
	} _CharacterWeaponSlot;
	
	// 카메라가 존재하는가?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool _BCamera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACWeaponGun> _WeaponRifleClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACWeaponGun> _WeaponPistolClass;
	
// ******************************************************************************************************
// methods
// ******************************************************************************************************
public:
	ACCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// 캐릭터 애니메이션 인터페이스 재정의
	FORCEINLINE virtual ECharacterActType GetCharacterActType() override { return _ActType; }
	FORCEINLINE virtual float GetGunIdleAnimationPlayRate() override { return _CharacterWeaponSlot.GunIdleAnimationPlayRate; }
	// 인게임 UMG 데이터 인터페이스 재정의
	FORCEINLINE virtual UCInGameUMGData* GetInGameUMGData() override { return _InGameUMGData; }

private:
	void ViewChange();
	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	void VerticalLook(float axisValue);
	void HorizontalLook(float axisValue);

protected:
	virtual void Action();
	virtual void Jump();
	virtual void Crouching();
	virtual void Crawl();
	virtual void BeginPlay() override;
	UFUNCTION() // AddDynamic에 함수를 바인딩할 경우 해당 함수는 반드시 UFUNCTION() 메크로를 사용해야, 안해도 에러는 발생X, 하지만 작동은 안함
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//ACWeapon* SpawnCharacterUsingObject(TSubclassOf<class ACWeaponGun> InActorClass, FTransform InSpawnTransform);
	ACWeapon* SpawnCharacterUsingObject(TSubclassOf<class ACWeapon> InActorClass, FName InSpawnSocketName);
	ACWeaponGun* SpawnCharacterUsingObject(TSubclassOf<class ACWeaponGun> InActorClass, FName InSpawnSocketName);
	void AttachCharacterUsingObject(class ACWeapon* InAttachWeapon, FName InAttackSocketName);
	void AttachCharacterUsingObject(class ACWeaponGun* InAttachWeapon, FName InAttackSocketName);
	//void AttachCharacterUsingObject(class ACWeaponKnife* InAttachWeapon, FName InAttackSocketName);
	//void AttachCharacterUsingObject(class ACWeaponGrenade* InAttachWeapon, FName InAttackSocketName);
};