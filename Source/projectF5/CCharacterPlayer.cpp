#include "CCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/TimelineComponent.h"

ACCharacterPlayer::ACCharacterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> _curve(TEXT("CurveFloat'/Game/Etc/AimCurve.AimCurve'"));
	check(_curve.Succeeded())
	_AimTimeline.AimCurve = _curve.Object;
}

void ACCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACCharacterPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction(TEXT("Rifle"), EInputEvent::IE_Pressed, this, &ACCharacterPlayer::Rifle);
	PlayerInputComponent->BindAction(TEXT("Pistol"), EInputEvent::IE_Pressed, this, &ACCharacterPlayer::Pistol);
	PlayerInputComponent->BindAction(TEXT("Knife"), EInputEvent::IE_Pressed, this, &ACCharacterPlayer::Knife);
	PlayerInputComponent->BindAction(TEXT("Grenade"), EInputEvent::IE_Pressed, this, &ACCharacterPlayer::Grenade);
	PlayerInputComponent->BindAction(TEXT("OnAim"), EInputEvent::IE_Pressed, this, &ACCharacterPlayer::OnAim);
	PlayerInputComponent->BindAction(TEXT("OffAim"), EInputEvent::IE_Released, this, &ACCharacterPlayer::OffAim);
}

void ACCharacterPlayer::Rifle()
{
	if (_CharacterWeaponSlot.BAiming) return;
	if (_CharacterWeaponSlot.CurrentWeaponSlotType != ECharacterWeaponSlotType::Rifle1) 
	{
		if (_CharacterWeaponSlot.CurrentWeaponSlotType != ECharacterWeaponSlotType::Max)
		{
			AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)_CharacterWeaponSlot.CurrentWeaponSlotType], _RifleHolsterSocketName);
		}
		AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Rifle1], _RifleEquipSocketName);
		_CharacterWeaponSlot.CurrentWeaponSlotType = ECharacterWeaponSlotType::Rifle1;
		_CharacterAnimation.WeaponAnimationType = ECharacterWeaponAnimationType::RifleEquipped;
	}
	else
	{
		AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Rifle1], _RifleHolsterSocketName);
		_CharacterWeaponSlot.CurrentWeaponSlotType = ECharacterWeaponSlotType::Max;
		_CharacterAnimation.WeaponAnimationType = ECharacterWeaponAnimationType::UnEquipped;
	}
}

void ACCharacterPlayer::Pistol()
{
	if (_CharacterWeaponSlot.BAiming) return;
	//if (_CharacterWeaponSlot.CurrentWeaponSlotType != ECharacterWeaponSlotType::Pistol2)
	//{
	//	if (_CharacterWeaponSlot.CurrentWeaponSlotType != ECharacterWeaponSlotType::Max)
	//	{
	//		AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)_CharacterWeaponSlot.CurrentWeaponSlotType], _RifleHolsterSocketName);
	//	}
	//	AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Pistol2], _RifleEquipHipSocketName);
	//	_CharacterWeaponSlot.CurrentWeaponSlotType = ECharacterWeaponSlotType::Pistol2;
	//}
	//else
	//{
	//	AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Pistol2], _RifleHolsterSocketName);
	//	_CharacterWeaponSlot.CurrentWeaponSlotType = ECharacterWeaponSlotType::Max;
	//}
}

void ACCharacterPlayer::Knife()
{
	//if (_CharacterWeaponSlot.CurrentWeaponSlotType != ECharacterWeaponSlotType::Knife3)
	//{
	//	if (_CharacterWeaponSlot.CurrentWeaponSlotType != ECharacterWeaponSlotType::Max)
	//	{
	//		AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)_CharacterWeaponSlot.CurrentWeaponSlotType], _RifleHolsterSocketName);
	//	}
	//	AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Knife3], _RifleEquipHipSocketName);
	//	_CharacterWeaponSlot.CurrentWeaponSlotType = ECharacterWeaponSlotType::Knife3;
	//}
	//else
	//{
	//	AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Knife3], _RifleHolsterSocketName);
	//	_CharacterWeaponSlot.CurrentWeaponSlotType = ECharacterWeaponSlotType::Max;
	//}
}

void ACCharacterPlayer::Grenade()
{
	//if (_CharacterWeaponSlot.CurrentWeaponSlotType != ECharacterWeaponSlotType::Grenade4)
	//{
	//	if (_CharacterWeaponSlot.CurrentWeaponSlotType != ECharacterWeaponSlotType::Max)
	//	{
	//		AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)_CharacterWeaponSlot.CurrentWeaponSlotType], _RifleHolsterSocketName);
	//	}
	//	AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Grenade4], _RifleEquipHipSocketName);
	//	_CharacterWeaponSlot.CurrentWeaponSlotType = ECharacterWeaponSlotType::Grenade4;
	//}
	//else
	//{
	//	AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Grenade4], _RifleHolsterSocketName);
	//	_CharacterWeaponSlot.CurrentWeaponSlotType = ECharacterWeaponSlotType::Max;
	//}
}

// https://www.youtube.com/watch?v=VaQMciMrN3s 참고
// https://www.youtube.com/watch?v=bUGb8x_qYW0 참고
void ACCharacterPlayer::OnAim()
{
	if (_CharacterWeaponSlot.CurrentWeaponSlotType == ECharacterWeaponSlotType::Rifle1 || _CharacterWeaponSlot.CurrentWeaponSlotType == ECharacterWeaponSlotType::Pistol2)
	{
		if (!_CharacterWeaponSlot.BAiming)
		{
			_CharacterWeaponSlot.BAiming = true;
			_CharacterAnimation.GunIdleAnimationPlayRate = 0.0f;
			_AimTimeline.AimTimeline->Play();
			_CameraComponent->SetFieldOfView(UKismetMathLibrary::Lerp(45.0f, 90.0f, _AimTimeline.InterpFloat));
			// 임시 무기마다 달라야 
			_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Rifle1]->AttachWeaponUsingObject(_CameraComponent, _ADSSocketName);/*AttachToComponent(_CameraComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, _RifleADSSocketName);*/
		}
	}
}

void ACCharacterPlayer::OffAim()
{
	if (_CharacterWeaponSlot.CurrentWeaponSlotType == ECharacterWeaponSlotType::Rifle1 || _CharacterWeaponSlot.CurrentWeaponSlotType == ECharacterWeaponSlotType::Pistol2)
	{
		if (_CharacterWeaponSlot.BAiming)
		{
			_CharacterWeaponSlot.BAiming = false;
			_CharacterAnimation.GunIdleAnimationPlayRate = 1.0f;
			_AimTimeline.AimTimeline->Play();
			_CameraComponent->SetFieldOfView(UKismetMathLibrary::Lerp(90.0f, 45.0f, _AimTimeline.InterpFloat));
			// 임시 무기마다 달라야 
			_CameraComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "head");
			_CameraComponent->SetRelativeRotation(FRotator(-100.0f, 0.0f, 75.0f));
			/*_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Rifle1]->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, _RifleEquipSocketName);*/

		}
	}
}

void ACCharacterPlayer::Action()
{
 
}

void ACCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	_AimTimeline.AimTimeline = NewObject<UTimelineComponent>(this, FName("AimTimeline"));
	_AimTimeline.OnAimTimelineCallback.BindUFunction(this, FName{ TEXT("AimTimelineUpdateCallback") });
	_AimTimeline.AimTimeline->AddInterpFloat(_AimTimeline.AimCurve, _AimTimeline.OnAimTimelineCallback);
	_AimTimeline.AimTimeline->SetPropertySetObject(this);

	// BP에서 설정하는 경우는 반드시 BeginPlay
	// https://stackoverflow.com/questions/59586835/why-cant-i-create-a-tsubclassof-to-use-in-a-spawnactor-function 참고
	if (_WeaponRifleClass) 
	{
		//_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Rifle1] = Cast<ACWeapon>(SpawnCharacterUsingObject(_WeaponRifleClass, _RifleHolsterSocketName));
		_CharacterWeaponSlot.Weapons.Insert(SpawnCharacterUsingObject(_WeaponRifleClass, _RifleHolsterSocketName), (uint8)ECharacterWeaponSlotType::Rifle1);
		if (_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Rifle1]) 
		{
			AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Rifle1], _RifleHolsterSocketName);
			_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Rifle1]->SetOwner(this);
		}
	}
}

void ACCharacterPlayer::AimTimelineUpdateCallback(float InterpValue)
{
	_AimTimeline.InterpFloat = InterpValue;
}