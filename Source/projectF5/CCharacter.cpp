#include "CCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
//#include "projectF5.h"
#include "CIteminterface.h"
#include "CWeapon.h"
#include "CInGameUMGData.h"

ACCharacter::ACCharacter()
	: _CharacterStats{ 0, 100.0f, 100.0f, 100.0f }, 
	_BCamera(true)
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = GetCapsuleComponent();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACCharacter::BeginOverlap);

	if (_BCamera)
	{
		_InGameUMGData->SetCharacterHp(_CharacterStats.Hp);
		_InGameUMGData->SetCharacterMp(_CharacterStats.Mp);
		_InGameUMGData->SetCharacterSp(_CharacterStats.Sp);

		_CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
		// below: https://forums.unrealengine.com/t/attaching-camera-to-head-socket/119911/3
		_CameraComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "head");
	}


	//// 임시: 캐릭터 소캣에다가 붙여줘야됨 코드 컴파일 확인하려고 임시 작성함
	//if (_WeaponClass)
	//{
	//	_Weapon = Cast<ACWeapon>(SpawnCharacterUsingObjectActorClassOriented(_WeaponClass));
	//}
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

		PlayerInputComponent->BindAction(TEXT("Action"), EInputEvent::IE_Pressed, this, &ACCharacter::Action);
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
		_CharacterStats.Hp += _itemInterface->ActivateItemAbility(); 
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

void ACCharacter::Action()
{

}

void ACCharacter::Jump()
{
	bPressedJump = true;
}

void ACCharacter::Crouching()
{
	//Super::Crouch();
	//ACharacter에 있는 함수
	//Crouch();
	//_ActType = ECharacterActType::Crouch;
}

void ACCharacter::Crawl()
{
	//_ActType = ECharacterActType::Crawl;
}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();

	//if(_SpringArmComponent) _SpringArmComponent->TargetArmLength = _CameraSpringArmLength;
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