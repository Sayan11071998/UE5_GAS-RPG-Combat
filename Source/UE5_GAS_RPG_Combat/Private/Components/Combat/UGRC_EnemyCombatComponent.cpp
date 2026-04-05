#include "Components/Combat/UGRC_EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "UGRC_GameplayTags.h"
#include "UGRC_FunctionLibrary.h"

void UUGRC_EnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;
	
	OverlappedActors.Add(HitActor);
	
	bool bIsValidBlock = false;
	
	const bool bIsPlayerBlocking = UUGRC_FunctionLibrary::NativeDoesActorHaveTag(HitActor, UGRC_GameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = UUGRC_FunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), UGRC_GameplayTags::Enemy_Status_Unblockable);
	
	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UUGRC_FunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}
	
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;
	
	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			UGRC_GameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			UGRC_GameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}