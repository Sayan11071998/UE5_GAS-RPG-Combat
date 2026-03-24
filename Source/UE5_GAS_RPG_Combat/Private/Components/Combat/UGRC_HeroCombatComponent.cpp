#include "Components/Combat/UGRC_HeroCombatComponent.h"
#include "Items/Weapons/UGRC_HeroWeapon.h"

AUGRC_HeroWeapon* UUGRC_HeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AUGRC_HeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}