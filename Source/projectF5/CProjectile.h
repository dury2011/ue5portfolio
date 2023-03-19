#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectile.generated.h"

// Gravity´Â ¸ðµç Projectile 1.0f
UCLASS()
class PROJECTF5_API ACProjectile : public AActor
{
	GENERATED_BODY()
// ******************************************************************************************************
// properties
// ******************************************************************************************************	
public:
	UPROPERTY(EditDefaultsOnly)
	float _ProjectileLifeSpan = 2.0f;
	
	//// unit: g(gram)
	//UPROPERTY(EditDefaultsOnly)
	//float _ProjectileWeight = 4.0f;

	// unit: cm/s(centimeter per second)
	UPROPERTY(EditDefaultsOnly)
	float _ProjectileSpeed = 94400.0f;

	UPROPERTY(EditDefaultsOnly)
	float _Damage = 100.0f;

	UPROPERTY(BlueprintReadOnly)
	FName _PhysicsMaterialHeadName = "PM_head";

	UPROPERTY(BlueprintReadOnly)
	FName _PhysicsMaterialBodyName = "PM_body";

	UPROPERTY(BlueprintReadOnly)
	FName _PhysicsMaterialArmsName = "PM_arms";

	UPROPERTY(BlueprintReadOnly)
	FName _PhysicsMaterialLegsName = "PM_legs";

	//UPROPERTY(EditDefaultsOnly)
	//float _ProjectileLineTraceDistance = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float _HeadDamageMultiply = 2.0f;

	UPROPERTY(EditDefaultsOnly)
	float _ArmsDamageDivide = 3.0f;

	UPROPERTY(EditDefaultsOnly)
	float _LegsDamageDivide = 2.0f;

	UPROPERTY(EditDefaultsOnly)
	bool _BPenetrate = false;

	// unit: J 
	UPROPERTY(BlueprintReadOnly)
	float _Force;

private:
	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* _ProjectileComponent;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* _SphereComponent;
	
	UPROPERTY()
	bool _BBeginOverlapOnce = true;
	//UPROPERTY(EditDefaultsOnly)
	//TSubclassOf<UDamageType> _DamageType;
	//UPROPERTY()
	//FHitResult _HitResult;

protected:

// ******************************************************************************************************
// methods
// ******************************************************************************************************

public:	
	ACProjectile();
	virtual void Tick(float DeltaTime) override;
	virtual void ShootProjectileToCrosshairDirection(const FVector& InFowardVector);
	
	//UFUNCTION()
	//virtual void Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private: 

protected:
	virtual void BeginPlay() override;
};
