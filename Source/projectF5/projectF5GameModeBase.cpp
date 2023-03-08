#include "projectF5GameModeBase.h"

AprojectF5GameModeBase::AprojectF5GameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> asset(TEXT("Blueprint'/Game/blueprint/BP_CharacterPlayer.BP_CharacterPlayer_C'"));
	DefaultPawnClass = asset.Class;
}