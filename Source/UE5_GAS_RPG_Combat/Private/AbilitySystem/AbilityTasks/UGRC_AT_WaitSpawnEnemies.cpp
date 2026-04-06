#include "AbilitySystem/AbilityTasks/UGRC_AT_WaitSpawnEnemies.h"

UUGRC_AT_WaitSpawnEnemies* UUGRC_AT_WaitSpawnEnemies::WaitSpawnEnemies(UGameplayAbility* OwningAbility,
	FGameplayTag EventTag, TSoftClassPtr<AUGRC_EnemyCharacter> SoftEnemyClassToSpawn, int32 NumToSpawn,
	const FVector& SpawnOrigin, float RandomSpawnRadius, const FRotator& SpawnRotation)
{
	UUGRC_AT_WaitSpawnEnemies* Node = NewAbilityTask<UUGRC_AT_WaitSpawnEnemies>(OwningAbility);
	Node->CachedEventTag = EventTag;
	Node->CachedSoftEnemyClassToSpawn = SoftEnemyClassToSpawn;
	Node->CachedNumToSpawn = NumToSpawn;
	Node->CachedSpawnOrigin = SpawnOrigin;
	Node->CachedRandomSpawnRadius = RandomSpawnRadius;
	Node->CachedSpawnRotation = SpawnRotation;
	
	return Node;
}