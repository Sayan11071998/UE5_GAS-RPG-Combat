#include "Components/Combat/UGRC_HeroCombatComponent.h"
#include "Items/Weapons/UGRC_HeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "UGRC_GameplayTags.h"

AUGRC_HeroWeapon* UUGRC_HeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AUGRC_HeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AUGRC_HeroWeapon* UUGRC_HeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AUGRC_HeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UUGRC_HeroCombatComponent::GetHeroCurrentEquippedWeaponDamageLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UUGRC_HeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;
	
	OverlappedActors.AddUnique(HitActor);
	
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		UGRC_GameplayTags::Shared_Event_MeleeHit,
		Data
	);
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		UGRC_GameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);
}

void UUGRC_HeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		UGRC_GameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);
}