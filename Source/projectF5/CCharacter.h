#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacterAnimationinterface.h"
#include "CCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterWeaponSlotType : uint8
{
	Weapon1, Weapon2, Weapon3, Weapon4, Max
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
	//UPROPERTY(EditDefaultsOnly)
	//class USpringArmComponent* _SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* _CameraComponent;

	UPROPERTY()
	ECharacterActType _ActType;

protected:
	// 캐릭터 스탯
	struct Stats
	{
		int32 Level;
		
		float Hp;
		float Mp;
		float Sp;
	} _CharacterStats;

	// 직접 플레이 가능한가?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool _BControl;

	// 카메라가 존재하는가?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool _BCamera;

	// 카메라 스프링 암 길이
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	//float _CameraSpringArmLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ACWeapon> _WeaponClass;

	// 배열로 만들 수 없을까?
	UPROPERTY()
	class ACWeapon* _Weapon;
// ******************************************************************************************************
// methods
// ******************************************************************************************************
public:
	ACCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// 캐릭터 애니메이션 인터페이스 재정의
	virtual ECharacterActType GetCharacterActType() override;


private:
	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	void VerticalLook(float axisValue);
	void HorizontalLook(float axisValue);
	void ViewChange();
	// 캐릭터가 사용하는 물체를 Spawn하고 AActor*로 반환 (zero location, zero rotator)
	AActor* SpawnCharacterUsingObjectActorClassOriented(TSubclassOf<class AActor> InActorClass, FTransform InSpawnTransform);
	// 캐릭터가 사용하는 물체를 Spawn하고 AActor*로 반환 (socket location, socket rotator)
	AActor* SpawnCharacterUsingObjectActorClassOriented(TSubclassOf<class AActor> InActorClass, FName InSpawnSocketName);
	
protected:
	virtual void Action();
	virtual void Jump();
	virtual void Crouching();
	virtual void Crawl();

	virtual void BeginPlay() override;
	UFUNCTION() // AddDynamic에 함수를 바인딩할 경우 해당 함수는 반드시 UFUNCTION() 메크로를 사용해야, 안해도 에러는 발생X, 하지만 작동은 안함
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};