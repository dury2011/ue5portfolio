#include "CCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ACCharacter::ACCharacter()
	: _CharacterStats{ 0, 100.0f, 100.0f, 100.0f }, _BControl(true), _BCamera(true), _CameraSpringArmLength(700.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = GetCapsuleComponent();

	//GetCharacterMovement()->bOrientRotationToMovement = false;
	//bUseControllerRotationYaw = true;
	//GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	if (_BControl && _BCamera)
	{
		_SpringArmComponent = CreateDefaultSubobject <USpringArmComponent>("Spring Arm Component");
		_SpringArmComponent->SetupAttachment(GetCapsuleComponent());
		_SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		_SpringArmComponent->TargetArmLength = 700.0f;
		_SpringArmComponent->bDoCollisionTest = false;
		_SpringArmComponent->bUsePawnControlRotation = true;
		_SpringArmComponent->SocketOffset = FVector(0.0f, 0.0f, 0.0f);
		_SpringArmComponent->bEnableCameraLag = true;
		_SpringArmComponent->CameraLagSpeed = 7.5f;
		_CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
		// UE4POFOL_F에서는 CHelpers.h로 확인해보니까 이렇게 되있는데? 이해가 안된다. 
		//_springArmComponent->SetupAttachment(NULL, "Camera Component");
		//SetRootComponent(_cameraComponent);
		// 그냥 이렇게 하면 안되나? 컴파일 결과 이렇게 해도 문제 없는 듯함. 
		_CameraComponent->SetupAttachment(_SpringArmComponent);
	}

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

void ACCharacter::Action()
{

}

void ACCharacter::Jump()
{
	bPressedJump = true;
}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
}