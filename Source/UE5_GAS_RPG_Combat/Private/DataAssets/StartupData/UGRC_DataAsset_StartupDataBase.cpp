#include "DataAssets/StartupData/UGRC_DataAsset_StartupDataBase.h"
#include "AbilitySystem/UGRC_AbilitySystemComponent.h"
#include "AbilitySystem/Abilities/UGRC_GameplayAbility.h"

void UUGRC_DataAsset_StartupDataBase::GiveToAbilitySystemComponent(
	TObjectPtr<UUGRC_AbilitySystemComponent> InCharacterASCToGive, int32 ApplyLevel)
{
	check(InCharacterASCToGive);
	
	GrantAbilities(ActivateOnGivenAbilities, InCharacterASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InCharacterASCToGive, ApplyLevel);
}

void UUGRC_DataAsset_StartupDataBase::GrantAbilities(
	const TArray<TSubclassOf<UUGRC_GameplayAbility>>& InAbilitiesToGive,
	TObjectPtr<UUGRC_AbilitySystemComponent> InCharacterASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) return;
	
	for (const TSubclassOf<UUGRC_GameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;
		
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InCharacterASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		InCharacterASCToGive->GiveAbility(AbilitySpec);
	}
}