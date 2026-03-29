#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartupData/UGRC_DataAsset_StartupDataBase.h"
#include "UGRC_DataAsset_EnemyStartupData.generated.h"

class UUGRC_EnemyGameplayAbility;

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_DataAsset_EnemyStartupData : public UUGRC_DataAsset_StartupDataBase
{
	GENERATED_BODY()
	
public:
	// ~ Begin UUGRC_DataAsset_StartupDataBase Interface
	virtual void GiveToAbilitySystemComponent(TObjectPtr<UUGRC_AbilitySystemComponent> InASCToGive, int32 ApplyLevel = 1) override;
	// ~ End UUGRC_DataAsset_StartupDataBase Interface
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UUGRC_EnemyGameplayAbility>> EnemyCombatAbilities;
};