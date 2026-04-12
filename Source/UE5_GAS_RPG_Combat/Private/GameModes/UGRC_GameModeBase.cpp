#include "GameModes/UGRC_GameModeBase.h"

AUGRC_GameModeBase::AUGRC_GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}