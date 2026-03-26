#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/UGRC_GameplayAbility.h"
#include "UGRC_EnemyGameplayAbility.generated.h"

class AUGRC_EnemyCharacter;
class UUGRC_EnemyCombatComponent;

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_EnemyGameplayAbility : public UUGRC_GameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "UGRC|Ability")
	AUGRC_EnemyCharacter* GetEnemyCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "UGRC|Ability")
	UUGRC_EnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();
	
private:
	TWeakObjectPtr<AUGRC_EnemyCharacter> CachedUGRCEnemyCharacter;
};