#include "CProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/EngineTypes.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/BodyInstance.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

ACProjectile::ACProjectile()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	_ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileComponent");
	_SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	RootComponent = _SphereComponent;

	if (_ProjectileComponent)
	{
		_ProjectileComponent->ProjectileGravityScale = 1.0f;
		_ProjectileComponent->InitialSpeed = _ProjectileSpeed;
		// Projectile Max 속도
		_ProjectileComponent->MaxSpeed = 100000.0f;
	}
	if (_SphereComponent)
	{
		// https://forums.unrealengine.com/t/physical-material-from-fhitresult-is-null/48444
		_SphereComponent->bReturnMaterialOnMove = true;
	}
}

void ACProjectile::BeginPlay()
{
	Super::BeginPlay();
	// https://forums.unrealengine.com/t/oncomponenthit-isnt-working/101955/5
	// 생성자에 있는거 다시 BeginPlay에 넣으니까 된다. 
	if (_SphereComponent)
	{
		_SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ACProjectile::BeginOverlap);
		//_SphereComponent->OnComponentHit.AddDynamic(this, &ACProjectile::Hit);
	}
}

void ACProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACProjectile::ShootProjectileToCrosshairDirection(const FVector& InFowardVector)
{
	_ProjectileComponent->Velocity = InFowardVector * _ProjectileComponent->InitialSpeed;
	SetLifeSpan(_ProjectileLifeSpan);
}

// https://www.youtube.com/watch?v=4dSsm_HIVV8
// https://stackoverflow.com/questions/57671756/empty-sweep-hit-result-on-overlap-with-projectile
void ACProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetOwner())
	if (OtherActor != this)
	if (OtherActor != GetOwner())
	if (_BBeginOverlapOnce)
	{
		_BBeginOverlapOnce = false;
		
		if (SweepResult.PhysMaterial->GetName() == _PhysicsMaterialHeadName.ToString())
		{
			_Damage *= _HeadDamageMultiply;
		}
		else if (SweepResult.PhysMaterial->GetName() == _PhysicsMaterialArmsName.ToString())
		{
			_Damage /= _ArmsDamageDivide;
		}
		else if (SweepResult.PhysMaterial->GetName() == _PhysicsMaterialLegsName.ToString())
		{
			_Damage /= _LegsDamageDivide;
		}

		UGameplayStatics::ApplyPointDamage(OtherActor, _Damage, GetActorLocation(), SweepResult, GetOwner()->GetInstigatorController(), this, NULL);
		
		if (!_BPenetrate)
		{
			Destroy();
		}

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("PhysMaterial: %s"), *FString(SweepResult.PhysMaterial->GetName())));
		}	
		UE_LOG(LogTemp, Warning, TEXT("ACProjectile::BeginOverlap Called!"));
		UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *FString(OtherActor->GetName()));
		UE_LOG(LogTemp, Warning, TEXT("OverlapBoneName: %s"), *FString(SweepResult.BoneName.ToString()));
		UE_LOG(LogTemp, Warning, TEXT("PhysMaterial: %s"), *FString(SweepResult.PhysMaterial->GetName()));
		UE_LOG(LogTemp, Warning, TEXT("bSweep: %d"), (uint8)bFromSweep);
	}
}

//void ACProjectile::Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	//// https://bbagwang.com/unreal-engine/ue4-%EC%97%90%EC%84%9C%EC%9D%98-trace/
//	//// https://forums.unrealengine.com/t/capsule-trace-in-c-function-appears-to-not-exist/33291
//	//// https://forums.unrealengine.com/t/skeletal-mesh-overlap-returns-null-bone/370880/6
//	//// https://forums.unrealengine.com/t/how-to-detect-if-a-bone-in-a-skeletal-mesh-is-overlapped/400893
//	//// https://www.youtube.com/watch?v=qOam3QjGE8g
//	//// https://bbagwang.com/unreal-engine/linetrace%EC%97%90%EC%84%9C-physical-material%EC%9D%B4-%EB%B0%9B%EC%95%84%EC%99%80%EC%A7%80%EC%A7%80-%EC%95%8A%EC%9D%84-%EB%95%8C/
//	//if (Hit.bBlockingHit)
//	//{
//	//	switch(Hit.PhysMaterial->SurfaceType.GetValue())
//	//	{
//	//		case SurfaceType1:
//	//		{
//	//			_Damage *= _HeadDamageMultiply;
//	//			break;
//	//		}
//	//		case SurfaceType2:
//	//		{
//	//			_Damage;
//	//			break;
//	//		}
//	//		case SurfaceType3:
//	//		{
//	//			_Damage /= _ArmsDamageDivide;
//	//			break;
//	//		}
//	//		case SurfaceType4:
//	//		{
//	//			_Damage /= _LegsDamageDivide;
//	//			break;
//	//		}
//	//		default:
//	//			break;
//	//	}
//	//	UGameplayStatics::ApplyPointDamage(OtherActor, _Damage, GetActorLocation(), Hit, GetInstigatorController(), this, nullptr);
//
//	//	UE_LOG(LogTemp, Warning, TEXT("PhysMat: %d"), (int8)(Hit.PhysMaterial->SurfaceType.GetValue()));
//	//	UE_LOG(LogTemp, Warning, TEXT("ACProjectie::Hit() Called"));
//	//}
//}