#include "Components/Combat/UGRC_PawnCombatComponent.h"
#include "Items/Weapons/UGRC_WeaponBase.h"
#include "Components/BoxComponent.h"

void UUGRC_PawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
	AUGRC_WeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A tag named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);
	
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
	
	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &UUGRC_PawnCombatComponent::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &UUGRC_PawnCombatComponent::OnWeaponPulledFromTargetActor);
	
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
}

AUGRC_WeaponBase* UUGRC_PawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AUGRC_WeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return  *FoundWeapon;
		}
	}
	
	return nullptr;
}

AUGRC_WeaponBase* UUGRC_PawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid()) return nullptr;
	
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UUGRC_PawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EUGRC_ToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EUGRC_ToggleDamageType::CurrentEquippedWeapon)
	{
		AUGRC_WeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();
		check(WeaponToToggle);
		
		if (bShouldEnable)
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			OverlappedActors.Empty();
		}
	}
}

void UUGRC_PawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UUGRC_PawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}