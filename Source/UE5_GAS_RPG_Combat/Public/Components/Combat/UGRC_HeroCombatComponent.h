#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/UGRC_PawnCombatComponent.h"
#include "UGRC_HeroCombatComponent.generated.h"

class AUGRC_HeroWeapon;

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_HeroCombatComponent : public UUGRC_PawnCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UGRC|Combat")
	AUGRC_HeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;
};