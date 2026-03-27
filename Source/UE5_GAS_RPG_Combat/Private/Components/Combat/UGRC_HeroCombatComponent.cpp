#include "Components/Combat/UGRC_HeroCombatComponent.h"
#include "Items/Weapons/UGRC_HeroWeapon.h"

#include "UGRC_DebugHelper.h"

AUGRC_HeroWeapon* UUGRC_HeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AUGRC_HeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

void UUGRC_HeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" hit ") + HitActor->GetActorNameOrLabel());
}

void UUGRC_HeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT("'s weapon pulled from ") + InteractedActor->GetActorNameOrLabel());
}