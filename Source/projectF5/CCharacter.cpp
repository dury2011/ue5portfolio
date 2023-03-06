#include "CCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
//#include "projectF5.h"
#include "CIteminterface.h"
#include "CWeapon.h"

ACCharacter::ACCharacter()
	: _ActType(ECharacterActType::Idle), _CharacterStats { 0, 100.0f, 100.0f, 100.0f }, _BControl(true), _BCamera(true)/*, _CameraSpringArmLength(700.0f)*/
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = GetCapsuleComponent();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACCharacter::BeginOverlap);
	//GetCharacterMovement()->bOrientRotationToMovement = false;
	//bUseControllerRotationYaw = true;
	//GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	if (_BControl && _BCamera)
	{
		//_SpringArmComponent = CreateDefaultSubobject <USpringArmComponent>("Spring Arm Component");
		//_SpringArmComponent->SetupAttachment(GetCapsuleComponent());
		//_SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		//_SpringArmComponent->TargetArmLength = _CameraSpringArmLength;
		//_SpringArmComponent->bDoCollisionTest = false;
		//_SpringArmComponent->bUsePawnControlRotation = true;
		//_SpringArmComponent->SocketOffset = FVector(0.0f, 0.0f, 0.0f);
		//_SpringArmComponent->bEnableCameraLag = true;
		//_SpringArmComponent->CameraLagSpeed = 7.5f;
		_CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
		// UE4POFOL_F에서는 CHelpers.h로 확인해보니까 이렇게 되있는데? 이해가 안된다. 
		//_springArmComponent->SetupAttachment(NULL, "Camera Component");
		//SetRootComponent(_cameraComponent);
		// 그냥 이렇게 하면 안되나? 컴파일 결과 이렇게 해도 문제 없는 듯함. 
		// _CameraComponent->SetupAttachment(_SpringArmComponent);
		// below: https://forums.unrealengine.com/t/attaching-camera-to-head-socket/119911/3
		//_CameraComponent->SetupAttachment(GetMesh());
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

	if (_BControl && _BCamera)
	{
		PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACCharacter::MoveForward);
		PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACCharacter::MoveRight);
		PlayerInputComponent->BindAxis(TEXT("VerticalLook"), this, &ACCharacter::VerticalLook);
		PlayerInputComponent->BindAxis(TEXT("HorizontalLook"), this, &ACCharacter::HorizontalLook);

		PlayerInputComponent->BindAction(TEXT("Action"), EInputEvent::IE_Pressed, this, &ACCharacter::Action);
		PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACCharacter::Jump);
		PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ACCharacter::Crouching);
		PlayerInputComponent->BindAction(TEXT("KneelDown"), EInputEvent::IE_Pressed, this, &ACCharacter::Crawl);
		PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &ACCharacter::ViewChange);
	}
}

ECharacterActType ACCharacter::GetCharacterActType()
{
	return _ActType;
}

void ACCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ICIteminterface* _itemInterface = Cast<ICIteminterface>(OtherActor);
	if (_itemInterface) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("Function Called: %s"), *FString("ACItem::TriggerBeginOverlap()")); 
		_CharacterStats.Hp += _itemInterface->ActivateItemAbility(); 
	}	
}

void ACCharacter::MoveForward(float axisValue)
{
	FRotator rotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotation).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, axisValue, true);
}

void ACCharacter::MoveRight(float axisValue)
{
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

AActor* ACCharacter::SpawnCharacterUsingObjectActorClassOriented(TSubclassOf<class AActor> InActorClass, FTransform InSpawnTransform)
{
	FActorSpawnParameters _params;
	_params.Owner = this;

	return GetWorld()->SpawnActor<AActor>(InActorClass, InSpawnTransform, _params);
}

AActor* ACCharacter::SpawnCharacterUsingObjectActorClassOriented(TSubclassOf<class AActor> InActorClass, FName InSpawnSocketName)
{
	FActorSpawnParameters _params;
	_params.Owner = this;

	return GetWorld()->SpawnActor<AActor>(InActorClass, GetMesh()->GetSocketTransform(InSpawnSocketName), _params);
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
	//_ActType = ECharacterActType::KneelDown;
}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();

	//if(_SpringArmComponent) _SpringArmComponent->TargetArmLength = _CameraSpringArmLength;
}