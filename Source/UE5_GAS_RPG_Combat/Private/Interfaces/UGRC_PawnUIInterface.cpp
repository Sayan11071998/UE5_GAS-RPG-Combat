#include "Interfaces/UGRC_PawnUIInterface.h"

TObjectPtr<UUGRC_HeroUIComponent> IUGRC_PawnUIInterface::GetHeroUIComponent() const
{
	return nullptr;
}

TObjectPtr<UUGRC_EnemyUIComponent> IUGRC_PawnUIInterface::GetEnemyUIComponent() const
{
	return nullptr;
}