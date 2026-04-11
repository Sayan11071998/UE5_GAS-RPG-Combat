#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/UGRC_GameplayAbility.h"
#include "UGRC_HeroGameplayAbility.generated.h"

class UUGRC_HeroUIComponent;
class AUGRC_HeroCharacter;
class AUGRC_HeroController;
class UUGRC_HeroCombatComponent;

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_HeroGameplayAbility : public UUGRC_GameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "UGRC|Ability")
	AUGRC_HeroCharacter* GetHeroCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "UGRC|Ability")
	AUGRC_HeroController* GetHeroControllerFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "UGRC|Ability")
	UUGRC_HeroCombatComponent* GetHeroCombatComponentFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "UGRC|Ability")
	UUGRC_HeroUIComponent* GetHeroUIComponentFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "UGRC|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);
	
	UFUNCTION(BlueprintCallable, Category = "UGRC|Ability")
	bool GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime);
	
private:
	TWeakObjectPtr<AUGRC_HeroCharacter> CachedUGRCHeroCharacter;
	TWeakObjectPtr<AUGRC_HeroController> CachedUGRCHeroController;
};