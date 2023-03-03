#include "projectF5GameModeBase.h"

AprojectF5GameModeBase::AprojectF5GameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> asset(TEXT("Blueprint'/Game/blueprint/BP_CCharacter_Test.BP_CCharacter_Test_C'"));
	DefaultPawnClass = asset.Class;
}