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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float _CameraSpringArmLength;
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

protected:
	virtual void Action();
	virtual void Jump();
	virtual void BeginPlay() override;
	UFUNCTION() // AddDynamic에 함수를 바인딩할 경우 해당 함수는 반드시 UFUNCTION() 메크로를 사용해야, 안해도 에러는 발생X, 하지만 작동은 안함
	virtual void TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
