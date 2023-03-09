#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

/* Transform 조정은 BP 확인 */
UCLASS()
class PROJECTF5_API ACWeapon : public AActor
{
	GENERATED_BODY()
// ******************************************************************************************************
// properties
// ******************************************************************************************************
public:
private:
protected:
	UPROPERTY(BlueprintReadOnly)
	class ACharacter* _Owner;

	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* _SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	class UCapsuleComponent* _CapsuleComponent;
// ******************************************************************************************************
// methods
// ******************************************************************************************************
public:	
	ACWeapon();
	virtual void Tick(float DeltaTime) override;
	void AttachWeaponUsingObject(class USceneComponent* InAttachComponent, FName InAttachSocketName);
private:

protected:
	virtual void BeginPlay() override;
	virtual void Attack(); 
};