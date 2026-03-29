#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CharacterTypes/UGRC_EnumTypes.h"
#include "UGRC_GameplayAbility.generated.h"

class UUGRC_PawnCombatComponent;
class UUGRC_AbilitySystemComponent;

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
	
	UFUNCTION(BlueprintPure, Category = "UGRC|Ability")
	UUGRC_PawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category = "UGRC|Ability")
	UUGRC_AbilitySystemComponent* GetUGRCAbilitySystemComponentFromActorInfo() const;
	
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);
	
	UFUNCTION(BlueprintCallable, Category = "UGRC|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EUGRC_SuccessType& OutSuccessType);
};