#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacter.generated.h"

UCLASS()
class PROJECTF5_API ACCharacter : public ACharacter
{
	GENERATED_BODY()
// ******************************************************************************************************
// properties
// ******************************************************************************************************
public:

private:
	UPROPERTY()
	class USpringArmComponent* _SpringArmComponent;

	UPROPERTY()
	class UCameraComponent* _CameraComponent;

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float _CameraSpringArmLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ACWeapon> _WeaponClass;

	// �迭�� ���� �� ������?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class ACWeapon* _Weapon;

// ******************************************************************************************************
// methods
// ******************************************************************************************************
public:
	ACCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	void VerticalLook(float axisValue);
	void HorizontalLook(float axisValue);
	// ĳ���Ͱ� ����ϴ� ��ü�� Spawn�ϰ� AActor*�� ��ȯ (zero location, zero rotator)
	AActor* SpawnCharacterUsingObjectActorClassOriented(TSubclassOf<class AActor> InActorClass);
	// ĳ���Ͱ� ����ϴ� ��ü�� Spawn�ϰ� AActor*�� ��ȯ (socket location, socket rotator)
	AActor* SpawnCharacterUsingObjectActorClassOriented(TSubclassOf<class AActor> InActorClass, FName InSpawnSocketName);

protected:
	virtual void Action();
	virtual void Jump();
	virtual void BeginPlay() override;
	UFUNCTION() // AddDynamic�� �Լ��� ���ε��� ��� �ش� �Լ��� �ݵ�� UFUNCTION() ��ũ�θ� ����ؾ�, ���ص� ������ �߻�X, ������ �۵��� ����
	virtual void TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};