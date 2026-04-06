#include "AbilitySystem/AbilityTasks/UGRC_AT_WaitSpawnEnemies.h"
#include "AbilitySystemComponent.h"

#include "UGRC_DebugHelper.h"

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

void UUGRC_AT_WaitSpawnEnemies::Activate()
{
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);
	
	DelegateHandle = Delegate.AddUObject(this, &UUGRC_AT_WaitSpawnEnemies::OnGameplayEventReceived);
}

void UUGRC_AT_WaitSpawnEnemies::OnDestroy(bool bInOwnerFinished)
{
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);
	
	Delegate.Remove(DelegateHandle);
	
	Super::OnDestroy(bInOwnerFinished);
}

void UUGRC_AT_WaitSpawnEnemies::OnGameplayEventReceived(const FGameplayEventData* InPayload)
{
	Debug::Print(TEXT("Gameplay Event Received"));
	
	EndTask();
}