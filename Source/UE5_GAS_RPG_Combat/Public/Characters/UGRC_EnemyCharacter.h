#pragma once

#include "CoreMinimal.h"
#include "Characters/UGRC_BaseCharacter.h"
#include "UGRC_EnemyCharacter.generated.h"

class UUGRC_EnemyCombatComponent;

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_EnemyCharacter : public AUGRC_BaseCharacter
{
	GENERATED_BODY()
	
public:
	AUGRC_EnemyCharacter();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UUGRC_EnemyCombatComponent> EnemyCombatComponent;
	
public:
	FORCEINLINE TObjectPtr<UUGRC_EnemyCombatComponent> GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};