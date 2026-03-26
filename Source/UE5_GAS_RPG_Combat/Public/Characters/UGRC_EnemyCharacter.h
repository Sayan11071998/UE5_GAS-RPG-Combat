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
	
	// ~ Begin IUGRC_PawnCombatInterface Interface
	virtual TObjectPtr<UUGRC_PawnCombatComponent> GetPawnCombatComponent() const override;
	// ~ End IUGRC_PawnCombatInterface Interface
	
protected:
	// ~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	// ~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UUGRC_EnemyCombatComponent> EnemyCombatComponent;
	
private:
	void InitEnemyStartupData();
	
public:
	FORCEINLINE TObjectPtr<UUGRC_EnemyCombatComponent> GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};