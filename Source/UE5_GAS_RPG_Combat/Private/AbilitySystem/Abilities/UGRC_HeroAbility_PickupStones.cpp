#include "AbilitySystem/Abilities/UGRC_HeroAbility_PickupStones.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/UGRC_HeroCharacter.h"
#include "Items/PickUps/UGRC_StoneBase.h"
#include "Components/UI/UGRC_HeroUIComponent.h"

void UUGRC_HeroAbility_PickupStones::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	GetHeroUIComponentFromActorInfo()->OnStoneInteracted.Broadcast(true);
}

void UUGRC_HeroAbility_PickupStones::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	GetHeroUIComponentFromActorInfo()->OnStoneInteracted.Broadcast(false);
}

void UUGRC_HeroAbility_PickupStones::CollectStones()
{
	CollectedStones.Empty();
	TArray<FHitResult> TraceHits;
	
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetHeroCharacterFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation(),
		GetHeroCharacterFromActorInfo()->GetActorLocation() + -GetHeroCharacterFromActorInfo()->GetActorUpVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		(-GetHeroCharacterFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		StoneTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		TraceHits,
		true
	);
	
	for (const FHitResult& TraceHit : TraceHits)
	{
		if (AUGRC_StoneBase* FoundStone = Cast<AUGRC_StoneBase>(TraceHit.GetActor()))
		{
			CollectedStones.AddUnique(FoundStone);
		}
	}
	
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}

void UUGRC_HeroAbility_PickupStones::ConsumeStones()
{
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}
	
	for (AUGRC_StoneBase* CollectedStone : CollectedStones)
	{
		if (CollectedStone)
		{
			CollectedStone->Consume(GetUGRCAbilitySystemComponentFromActorInfo(), GetAbilityLevel());
		}
	}
}