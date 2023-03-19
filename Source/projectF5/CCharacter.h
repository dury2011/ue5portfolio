#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacterAnimationinterface.h"
#include "CWeaponGun.h"
#include "CCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterWeaponSlotType : uint8
{
	Rifle1 = 0, Pistol2, Knife3, Grenade4, Max
};

// Transform ������ �������Ʈ���� ��

// Idle �� Aim�� ���� ���ϸ��̼� ���߰� �Ͽ��µ� �ƴ�
// Rifle, Pistol���� �߿��� ������ spine_01 ���� ���ϸ��̼� ������ �����ǵ��� ����
// ������ ���ۿ� ���Ͽ��� ���� �������
UCLASS()
class PROJECTF5_API ACCharacter : public ACharacter, public ICCharacterAnimationinterface
{
	GENERATED_BODY()
// ******************************************************************************************************
// properties
// ******************************************************************************************************
public:
private:
	//UPROPERTY()
	//class UCInGameUMGData* _InGameUMGData;

protected:
	// ĳ���� ����
	struct Stats
	{
		uint32 Level;
		float Hp;
		float Mp;
		float Sp;
	} _CharacterStat;

	struct WeaponSlot
	{
		// Aim �߿� ���� ���� ����
		bool BAiming;
		ECharacterWeaponSlotType CurrentWeaponSlotType = ECharacterWeaponSlotType::Max;
		//ECharacterWeaponFireSelectorType CurrentWeaponFireSelectorType = ECharacterWeaponFireSelectorType::Max;
		TArray<class ACWeapon*> Weapons;
	} _CharacterWeaponSlot;

	struct Animation
	{
		// Aim�߿� Idle �ִϸ��̼��� ����� ���Ƽ� �ִϸ��̼����� ���� ��鸲 ����
		float GunIdleAnimationPlayRate = 1.0f;
		ECharacterWeaponAnimationType WeaponAnimationType;
	}_CharacterAnimation;
	// ī�޶� �����ϴ°�?
	
	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* _CameraComponent;
	
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
	FORCEINLINE virtual ECharacterWeaponAnimationType GetCharacterWeaponAnimationType() override { return _CharacterAnimation.WeaponAnimationType; }
	FORCEINLINE virtual float GetGunIdleAnimationPlayRate() override { return _CharacterAnimation.GunIdleAnimationPlayRate; }
	FORCEINLINE UCameraComponent* GetCameraComponent() { return _CameraComponent; }
	FORCEINLINE ACWeapon* GetWeapon() { return _CharacterWeaponSlot.Weapons[(uint8)_CharacterWeaponSlot.CurrentWeaponSlotType]; }

private:
	void ViewChange();
	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	void VerticalLook(float axisValue);
	void HorizontalLook(float axisValue);

protected:
	virtual void OnAction();
	virtual void OffAction();
	virtual void Jump();
	virtual void Crouching();
	virtual void Crawl();
	UFUNCTION()
	virtual void DamagedPoint(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);
	// AActor�� �Լ��� BlueprintInplementableEvent, AActor���� ����, ��������Ʈ�� �ݹ��ؾ�
	/*virtual void ReceivePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);*/
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