#include "DataAssets/StartupData/UGRC_DataAsset_StartupDataBase.h"
#include "AbilitySystem/UGRC_AbilitySystemComponent.h"
#include "AbilitySystem/Abilities/UGRC_GameplayAbility.h"

void UUGRC_DataAsset_StartupDataBase::GiveToAbilitySystemComponent(
	TObjectPtr<UUGRC_AbilitySystemComponent> InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);
	
	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UUGRC_DataAsset_StartupDataBase::GrantAbilities(
	const TArray<TSubclassOf<UUGRC_GameplayAbility>>& InAbilitiesToGive,
	TObjectPtr<UUGRC_AbilitySystemComponent> InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) return;
	
	for (const TSubclassOf<UUGRC_GameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;
		
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		InASCToGive->GiveAbility(AbilitySpec);
	}
}