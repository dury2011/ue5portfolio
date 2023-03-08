#include "CCharacterPlayer.h"

ACCharacterPlayer::ACCharacterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
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
		AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Rifle1], _RifleEquipHipSocketName);
		_CharacterWeaponSlot.CurrentWeaponSlotType = ECharacterWeaponSlotType::Rifle1;
	}
	else
	{
		AttachCharacterUsingObject(_CharacterWeaponSlot.Weapons[(uint8)ECharacterWeaponSlotType::Rifle1], _RifleHolsterSocketName);
		_CharacterWeaponSlot.CurrentWeaponSlotType = ECharacterWeaponSlotType::Max;
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

void ACCharacterPlayer::OnAim()
{
	if (_CharacterWeaponSlot.CurrentWeaponSlotType == ECharacterWeaponSlotType::Rifle1 || _CharacterWeaponSlot.CurrentWeaponSlotType == ECharacterWeaponSlotType::Pistol2)
	{
		if (!_CharacterWeaponSlot.BAiming)
		{
			_CharacterWeaponSlot.BAiming = true;
			_CharacterWeaponSlot.GunIdleAnimationPlayRate = 0.0f;
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
			_CharacterWeaponSlot.GunIdleAnimationPlayRate = 1.0f;
		}
	}
}

void ACCharacterPlayer::Action()
{
 
}

void ACCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	// BP에서 설정하는 경우는 반드시 BeginPlay
	// below: https://stackoverflow.com/questions/59586835/why-cant-i-create-a-tsubclassof-to-use-in-a-spawnactor-function
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