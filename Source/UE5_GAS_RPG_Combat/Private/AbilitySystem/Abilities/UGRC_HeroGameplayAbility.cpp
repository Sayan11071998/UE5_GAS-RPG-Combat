#include "AbilitySystem/Abilities/UGRC_HeroGameplayAbility.h"
#include "AbilitySystem/UGRC_AbilitySystemComponent.h"
#include "Characters/UGRC_HeroCharacter.h"
#include "Controllers/UGRC_HeroController.h"
#include "AbilitySystem/Abilities/UGRC_GameplayAbility.h"
#include "UGRC_GameplayTags.h"

AUGRC_HeroCharacter* UUGRC_HeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedUGRCHeroCharacter.IsValid())
	{
		CachedUGRCHeroCharacter = Cast<AUGRC_HeroCharacter>(CurrentActorInfo->AvatarActor);
	}
	
	return CachedUGRCHeroCharacter.IsValid() ? CachedUGRCHeroCharacter.Get() : nullptr;
}

AUGRC_HeroController* UUGRC_HeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedUGRCHeroController.IsValid())
	{
		CachedUGRCHeroController = Cast<AUGRC_HeroController>(CurrentActorInfo->PlayerController);
	}
	
	return CachedUGRCHeroController.IsValid() ? CachedUGRCHeroController.Get() : nullptr;
}

UUGRC_HeroCombatComponent* UUGRC_HeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle UUGRC_HeroGameplayAbility::MakeHeroDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag,
	int32 InUsedComboCount)
{
	check(EffectClass);
	
	FGameplayEffectContextHandle ContextHandle = GetUGRCAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	
	FGameplayEffectSpecHandle EffectSpecHandle = GetUGRCAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);
	
	EffectSpecHandle.Data->SetSetByCallerMagnitude(UGRC_GameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);
	
	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}
	
	return EffectSpecHandle;
}