#include "DataAssets/StartupData/UGRC_DataAsset_EnemyStartupData.h"
#include "AbilitySystem/Abilities/UGRC_EnemyGameplayAbility.h"
#include "AbilitySystem/UGRC_AbilitySystemComponent.h"

void UUGRC_DataAsset_EnemyStartupData::GiveToAbilitySystemComponent(
	TObjectPtr<UUGRC_AbilitySystemComponent> InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	
	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf<UUGRC_EnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass) continue;
			
			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			
			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}