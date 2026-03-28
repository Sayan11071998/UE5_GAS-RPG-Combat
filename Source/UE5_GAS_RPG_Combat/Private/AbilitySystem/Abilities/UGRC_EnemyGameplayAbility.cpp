#include "AbilitySystem/Abilities/UGRC_EnemyGameplayAbility.h"
#include "Characters/UGRC_EnemyCharacter.h"

AUGRC_EnemyCharacter* UUGRC_EnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedUGRCEnemyCharacter.IsValid())
	{
		CachedUGRCEnemyCharacter = Cast<AUGRC_EnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	
	return CachedUGRCEnemyCharacter.IsValid() ? CachedUGRCEnemyCharacter.Get() : nullptr;
}

UUGRC_EnemyCombatComponent* UUGRC_EnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}