#include "DataAssets/StartupData/UGRC_DataAsset_HeroStartupData.h"
#include "AbilitySystem/Abilities/UGRC_GameplayAbility.h"
#include "AbilitySystem/UGRC_AbilitySystemComponent.h"

bool FUGRC_HeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}

void UUGRC_DataAsset_HeroStartupData::GiveToAbilitySystemComponent(TObjectPtr<UUGRC_AbilitySystemComponent> InASCToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	
	for (const FUGRC_HeroAbilitySet& AbilitySet : HeroStartupAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;
		
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		
		InASCToGive->GiveAbility(AbilitySpec);
	}
}