#include "AbilitySystem/Abilities/UGRC_GameplayAbility.h"
#include "AbilitySystem/UGRC_AbilitySystemComponent.h"
#include "Components/Combat/UGRC_PawnCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

void UUGRC_GameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	if (AbilityActivationPolicy == EUGRC_AbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UUGRC_GameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	if (AbilityActivationPolicy == EUGRC_AbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UUGRC_PawnCombatComponent* UUGRC_GameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UUGRC_PawnCombatComponent>();
}

UUGRC_AbilitySystemComponent* UUGRC_GameplayAbility::GetUGRCAbilitySystemComponentFromActorInfo() const
{
	return Cast<UUGRC_AbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UUGRC_GameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	
	check(TargetASC && InSpecHandle.IsValid());
	
	return GetUGRCAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);
}

FActiveGameplayEffectHandle UUGRC_GameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle, EUGRC_SuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);
	
	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EUGRC_SuccessType::Successful : EUGRC_SuccessType::Failed;
	
	return ActiveGameplayEffectHandle;
}