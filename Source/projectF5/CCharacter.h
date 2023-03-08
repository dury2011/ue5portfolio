#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacterAnimationinterface.h"
#include "CInGameUMGinterface.h"
#include "CWeaponGun.h"
#include "CCharacter.generated.h"



// Transform ������ �������Ʈ���� ��
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
	// ĳ���� ����
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
		// Aim�߿� Idle �ִϸ��̼��� ����� ���Ƽ� �ִϸ��̼����� ���� ��鸲 ����
		float GunIdleAnimationPlayRate = 1.0f;
		ECharacterWeaponSlotType CurrentWeaponSlotType = ECharacterWeaponSlotType::Max;
		TArray<class ACWeapon*> Weapons;
	} _CharacterWeaponSlot;
	
	// ī�޶� �����ϴ°�?
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
	// ĳ���� �ִϸ��̼� �������̽� ������
	FORCEINLINE virtual ECharacterActType GetCharacterActType() override { return _ActType; }
	FORCEINLINE virtual float GetGunIdleAnimationPlayRate() override { return _CharacterWeaponSlot.GunIdleAnimationPlayRate; }
	// �ΰ��� UMG ������ �������̽� ������
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
	UFUNCTION() // AddDynamic�� �Լ��� ���ε��� ��� �ش� �Լ��� �ݵ�� UFUNCTION() ��ũ�θ� ����ؾ�, ���ص� ������ �߻�X, ������ �۵��� ����
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//ACWeapon* SpawnCharacterUsingObject(TSubclassOf<class ACWeaponGun> InActorClass, FTransform InSpawnTransform);
	ACWeapon* SpawnCharacterUsingObject(TSubclassOf<class ACWeapon> InActorClass, FName InSpawnSocketName);
	ACWeaponGun* SpawnCharacterUsingObject(TSubclassOf<class ACWeaponGun> InActorClass, FName InSpawnSocketName);
	void AttachCharacterUsingObject(class ACWeapon* InAttachWeapon, FName InAttackSocketName);
	void AttachCharacterUsingObject(class ACWeaponGun* InAttachWeapon, FName InAttackSocketName);
	//void AttachCharacterUsingObject(class ACWeaponKnife* InAttachWeapon, FName InAttackSocketName);
	//void AttachCharacterUsingObject(class ACWeaponGrenade* InAttachWeapon, FName InAttackSocketName);
};