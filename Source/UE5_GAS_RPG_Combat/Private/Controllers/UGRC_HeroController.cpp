#include "Controllers/UGRC_HeroController.h"

AUGRC_HeroController::AUGRC_HeroController()
{
	HeroTeamID = FGenericTeamId(0);
}

FGenericTeamId AUGRC_HeroController::GetGenericTeamId() const
{
	return HeroTeamID;
}