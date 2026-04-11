#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/UGRC_HeroGameplayAbility.h"
#include "UGRC_HeroAbility_PickupStones.generated.h"

class AUGRC_StoneBase;

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_HeroAbility_PickupStones : public UUGRC_HeroGameplayAbility
{
	GENERATED_BODY()
	
protected:
	// ~ Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// ~ End UGameplayAbility Interface
	
	UFUNCTION(BlueprintCallable)
	void CollectStones();
	
private:
	UPROPERTY(EditDefaultsOnly)
	float BoxTraceDistance = 50.f;
	
	UPROPERTY(EditDefaultsOnly)
	FVector TraceBoxSize = FVector(100.f);
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> StoneTraceChannel;
	
	UPROPERTY(EditDefaultsOnly)
	bool bDrawDebugShape = false;
	
	UPROPERTY()
	TArray<AUGRC_StoneBase*> CollectedStones;
};