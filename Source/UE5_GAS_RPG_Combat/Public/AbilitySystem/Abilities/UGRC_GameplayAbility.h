#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "UGRC_GameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EUGRC_AbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	// ~ Begin UGameplayAbility Interface
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// ~ End UGameplayAbility Interface
	
	UPROPERTY(EditDefaultsOnly, Category = "UGRC Ability")
	EUGRC_AbilityActivationPolicy AbilityActivationPolicy = EUGRC_AbilityActivationPolicy::OnTriggered;
};