#include "AbilitySystem/Abilities/UGRC_HeroAbility_TargetLock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/UGRC_HeroCharacter.h"
#include "Kismet/GameplayStatics.h"

#include "UGRC_DebugHelper.h"

void UUGRC_HeroAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UUGRC_HeroAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Cleanup();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UUGRC_HeroAbility_TargetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();
	
	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}
	
	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);
	
	if (CurrentLockedActor)
	{
		Debug::Print(CurrentLockedActor->GetActorNameOrLabel());
	}
	else
	{
		CancelTargetLockAbility();
	}
}

void UUGRC_HeroAbility_TargetLock::GetAvailableActorsToLock()
{
	TArray<FHitResult> BoxTraceHits;
	
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetHeroCharacterFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation(),
		GetHeroCharacterFromActorInfo()->GetActorLocation() + GetHeroCharacterFromActorInfo()->GetActorForwardVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		GetHeroCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);
	
	for (const FHitResult& TraceHit : BoxTraceHits)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			if (HitActor != GetHeroCharacterFromActorInfo())
			{
				AvailableActorsToLock.AddUnique(HitActor);
			}
		}
	}
}

TObjectPtr<AActor> UUGRC_HeroAbility_TargetLock::GetNearestTargetFromAvailableActors(
	const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = 0.f;
	
	return UGameplayStatics::FindNearestActor(
		GetHeroCharacterFromActorInfo()->GetActorLocation(),
		InAvailableActors,
		ClosestDistance
	);
}

void UUGRC_HeroAbility_TargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UUGRC_HeroAbility_TargetLock::Cleanup()
{
	AvailableActorsToLock.Empty();
	CurrentLockedActor = nullptr;
}