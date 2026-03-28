#pragma once

#include "CoreMinimal.h"
#include "Characters/UGRC_BaseCharacter.h"
#include "UGRC_EnemyCharacter.generated.h"

class UUGRC_EnemyCombatComponent;
class UUGRC_EnemyUIComponent;

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_EnemyCharacter : public AUGRC_BaseCharacter
{
	GENERATED_BODY()
	
public:
	AUGRC_EnemyCharacter();
	
	// ~ Begin IUGRC_PawnCombatInterface Interface
	virtual TObjectPtr<UUGRC_PawnCombatComponent> GetPawnCombatComponent() const override;
	// ~ End IUGRC_PawnCombatInterface Interface
	
	// ~ Begin IUGRC_PawnUIInterface Interface
	virtual TObjectPtr<UUGRC_PawnUIComponent> GetPawnUIComponent() const override;
	// ~ End IUGRC_PawnUIInterface Interface
	
protected:
	// ~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	// ~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UUGRC_EnemyCombatComponent> EnemyCombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UUGRC_EnemyUIComponent> EnemyUIComponent;
	
private:
	void InitEnemyStartupData();
	
public:
	FORCEINLINE TObjectPtr<UUGRC_EnemyCombatComponent> GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};