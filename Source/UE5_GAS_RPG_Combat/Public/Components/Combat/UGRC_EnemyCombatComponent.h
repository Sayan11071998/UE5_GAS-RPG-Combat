#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/UGRC_PawnCombatComponent.h"
#include "UGRC_EnemyCombatComponent.generated.h"

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_EnemyCombatComponent : public UUGRC_PawnCombatComponent
{
	GENERATED_BODY()
	
public:
	// ~ Begin UUGRC_EnemyCombatComponent Interface
	virtual void OnHitTargetActor(AActor* HitActor) override;
	// ~ End UUGRC_EnemyCombatComponent Interface
	
protected:
	// ~ Begin UUGRC_PawnCombatComponent Interface
	virtual void ToggleBodyCollisionBoxCollision(bool bShouldEnable, EUGRC_ToggleDamageType ToggleDamageType) override;
	// ~ End UUGRC_PawnCombatComponent Interface
};