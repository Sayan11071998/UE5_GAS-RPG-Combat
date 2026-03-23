#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UGRC_DataAsset_StartupDataBase.generated.h"

class UUGRC_GameplayAbility;
class UUGRC_AbilitySystemComponent;

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_DataAsset_StartupDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(TObjectPtr<UUGRC_AbilitySystemComponent> InCharacterASCToGive, int32 ApplyLevel = 1);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UUGRC_GameplayAbility>> ActivateOnGivenAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UUGRC_GameplayAbility>> ReactiveAbilities;
	
	void GrantAbilities(const TArray<TSubclassOf<UUGRC_GameplayAbility>>& InAbilitiesToGive, TObjectPtr<UUGRC_AbilitySystemComponent> InCharacterAbilityToGive, int32 ApplyLevel = 1);
};