#include "CCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
//#include "projectF5.h"
#include "CIteminterface.h"
#include "CWeapon.h"
#include "CInGameUMGData.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

ACCharacter::ACCharacter()
	: _CharacterStat{ 0, 1000.0f, 1000.0f, 1000.0f }, 
	_BCamera(true)
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = GetCapsuleComponent();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACCharacter::BeginOverlap);
	OnTakePointDamage.AddDynamic(this, &ACCharacter::DamagedPoint);

	if (_BCamera)
	{
		_CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
		// https://forums.unrealengine.com/t/attaching-camera-to-head-socket/119911/3
		_CameraComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "head");
	}
}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (_BCamera)
	{
		PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACCharacter::MoveForward);
		PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACCharacter::MoveRight);
		PlayerInputComponent->BindAxis(TEXT("VerticalLook"), this, &ACCharacter::VerticalLook);
		PlayerInputComponent->BindAxis(TEXT("HorizontalLook"), this, &ACCharacter::HorizontalLook);

		PlayerInputComponent->BindAction(TEXT("OnAction"), EInputEvent::IE_Pressed, this, &ACCharacter::OnAction);
		PlayerInputComponent->BindAction(TEXT("OffAction"), EInputEvent::IE_Released, this, &ACCharacter::OffAction);
		PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACCharacter::Jump);
		PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ACCharacter::Crouching);
		PlayerInputComponent->BindAction(TEXT("Crawl"), EInputEvent::IE_Pressed, this, &ACCharacter::Crawl);
		PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &ACCharacter::ViewChange);
	}
}

void ACCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ICIteminterface* _itemInterface = Cast<ICIteminterface>(OtherActor);
	if (_itemInterface) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("Function Called: %s"), *FString("ACCharacter::TriggerBeginOverlap()")); 
		_CharacterStat.Hp += _itemInterface->ActivateItemAbility(); 
	}	
}

void ACCharacter::MoveForward(float axisValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("Function Called: %s"), *FString("ACCharacter::MoveForward()"));

	FRotator rotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotation).GetForwardVector().GetSafeNormal2D();
	AddMovementInput(direction, axisValue, true);
}

void ACCharacter::MoveRight(float axisValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("Function Called: %s"), *FString("ACCharacter::MoveRight()"));
	
	FRotator rotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotation).GetRightVector().GetSafeNormal2D();
	AddMovementInput(direction, axisValue, true);
}

void ACCharacter::VerticalLook(float axisValue)
{
	AddControllerPitchInput(axisValue);
}

void ACCharacter::HorizontalLook(float axisValue)
{
	AddControllerYawInput(axisValue);
}

// below: https://www.youtube.com/watch?v=0mgm16ki8zM&list=PLL0cLF8gjBprG6487lxqSq-aEo6ZXLDLg&index=2
void ACCharacter::ViewChange()
{
	
}

void ACCharacter::OnAction()
{

}

void ACCharacter::OffAction()
{

}

void ACCharacter::Jump()
{
	bPressedJump = true;
}

void ACCharacter::Crouching()
{

}

void ACCharacter::Crawl()
{

}

//https://hannom.tistory.com/200
void ACCharacter::DamagedPoint(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser)
{	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Damage %f"), Damage));
	}

	_CharacterStat.Hp -= Damage;

	// 임시
	if (_CharacterStat.Hp <= 0)
	{
		GetMesh()->SetSimulatePhysics(true);
		SetLifeSpan(5.0f);
	}
		
	UE_LOG(LogTemp, Warning, TEXT("ACCharacter::DamagedPoint Called!"));
	//FPointDamageEvent* const _pointDamageE = (FPointDamageEvent*)&DamageEvent;
	//// 비 const 참조에 대한 초기값은 R-Value여야 합니다. 
	//const auto& _surfaceType = _pointDamageE->HitInfo.PhysMaterial.Get()->SurfaceType.GetValue();
	//// 1:head, 2:body, 3:amrs, 4:legs
	//switch (_surfaceType)
	//{
	//	case SurfaceType1:
	//	{
	//		_CharacterStat.Hp -= _finalDamage * 2;
	//		break;
	//	}
	//	case SurfaceType2:
	//	{
	//		_CharacterStat.Hp -= _finalDamage;
	//		break;
	//	}
	//	case SurfaceType3:
	//	{
	//		_CharacterStat.Hp -= _finalDamage / 2.0f;
	//		break;
	//	}
	//	case SurfaceType4:
	//	{
	//		_CharacterStat.Hp -= _finalDamage / 3.0f;
	//		break;
	//	}
	//}
}

//void ACCharacter::ReceivePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser)
//{
//
//}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();

	//_InGameUMGData->SetCharacterHp(_CharacterStats.Hp);
	//_InGameUMGData->SetCharacterMp(_CharacterStats.Mp);
	//_InGameUMGData->SetCharacterSp(_CharacterStats.Sp);
}

ACWeapon* ACCharacter::SpawnCharacterUsingObject(TSubclassOf<class ACWeapon> InActorClass, FName InSpawnSocketName)
{
	FActorSpawnParameters _params;
	_params.Owner = this;

	return GetWorld()->SpawnActor<ACWeapon>(InActorClass, GetMesh()->GetSocketTransform(InSpawnSocketName), _params);
}

ACWeaponGun* ACCharacter::SpawnCharacterUsingObject(TSubclassOf<class ACWeaponGun> InActorClass, FName InSpawnSocketName)
{
	FActorSpawnParameters _params;
	_params.Owner = this;

	return GetWorld()->SpawnActor<ACWeaponGun>(InActorClass, GetMesh()->GetSocketTransform(InSpawnSocketName), _params);
}

void ACCharacter::AttachCharacterUsingObject(class ACWeaponGun* InAttachWeapon, FName InAttackSocketName)
{
	InAttachWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, InAttackSocketName);
}

void ACCharacter::AttachCharacterUsingObject(class ACWeapon* InAttachWeapon, FName InAttackSocketName)
{
	InAttachWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, InAttackSocketName);
}