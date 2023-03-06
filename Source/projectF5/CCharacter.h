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

// Transform ������ �������Ʈ���� ��
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
	// ĳ���� ����
	struct Stats
	{
		int32 Level;
		
		float Hp;
		float Mp;
		float Sp;
	} _CharacterStats;

	// ���� �÷��� �����Ѱ�?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool _BControl;

	// ī�޶� �����ϴ°�?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool _BCamera;

	// ī�޶� ������ �� ����
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	//float _CameraSpringArmLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ACWeapon> _WeaponClass;

	// �迭�� ���� �� ������?
	UPROPERTY()
	class ACWeapon* _Weapon;
// ******************************************************************************************************
// methods
// ******************************************************************************************************
public:
	ACCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// ĳ���� �ִϸ��̼� �������̽� ������
	virtual ECharacterActType GetCharacterActType() override;


private:
	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	void VerticalLook(float axisValue);
	void HorizontalLook(float axisValue);
	void ViewChange();
	// ĳ���Ͱ� ����ϴ� ��ü�� Spawn�ϰ� AActor*�� ��ȯ (zero location, zero rotator)
	AActor* SpawnCharacterUsingObjectActorClassOriented(TSubclassOf<class AActor> InActorClass, FTransform InSpawnTransform);
	// ĳ���Ͱ� ����ϴ� ��ü�� Spawn�ϰ� AActor*�� ��ȯ (socket location, socket rotator)
	AActor* SpawnCharacterUsingObjectActorClassOriented(TSubclassOf<class AActor> InActorClass, FName InSpawnSocketName);
	
protected:
	virtual void Action();
	virtual void Jump();
	virtual void Crouching();
	virtual void Crawl();

	virtual void BeginPlay() override;
	UFUNCTION() // AddDynamic�� �Լ��� ���ε��� ��� �ش� �Լ��� �ݵ�� UFUNCTION() ��ũ�θ� ����ؾ�, ���ص� ������ �߻�X, ������ �۵��� ����
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};