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
	
	UFUNCTION(BlueprintCallable, Category = "UGRC|Combat")
	AUGRC_HeroWeapon* GetHeroCurrentEquippedWeapon() const;
	
	UFUNCTION(BlueprintCallable, Category = "UGRC|Combat")
	float GetHeroCurrentEquippedWeaponDamageLevel(float InLevel) const;
	
	// ~ Begin UUGRC_PawnCombatComponent Interface
	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
	// ~ End UUGRC_PawnCombatComponent Interface
};