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

// Transform 조정은 블루프린트에서 함
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
	// 캐릭터 스탯
	struct Stats
	{
		uint32 Level;
		float Hp;
		float Mp;
		float Sp;
	} _CharacterStats;

	struct WeaponSlot
	{
		// Aim 중에 무기 변경 금지
		bool BAiming;
		ECharacterWeaponSlotType CurrentWeaponSlotType = ECharacterWeaponSlotType::Max;
		//ECharacterWeaponFireSelectorType CurrentWeaponFireSelectorType = ECharacterWeaponFireSelectorType::Max;
		TArray<class ACWeapon*> Weapons;
	} _CharacterWeaponSlot;

	struct Animation
	{
		// Aim중에 Idle 애니메이션의 재생을 막아서 애니메이션으로 인한 흔들림 방지
		float GunIdleAnimationPlayRate = 1.0f;
		ECharacterWeaponAnimationType WeaponAnimationType;
	}_CharacterAnimation;
	// 카메라가 존재하는가?
	
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
	// 캐릭터 애니메이션 인터페이스 재정의
	FORCEINLINE virtual ECharacterWeaponAnimationType GetCharacterWeaponAnimationType() override { return _CharacterAnimation.WeaponAnimationType; }
	FORCEINLINE virtual float GetGunIdleAnimationPlayRate() override { return _CharacterAnimation.GunIdleAnimationPlayRate; }

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