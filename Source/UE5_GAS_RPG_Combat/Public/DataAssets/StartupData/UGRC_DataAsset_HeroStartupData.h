#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartupData/UGRC_DataAsset_StartupDataBase.h"
#include "GameplayTagContainer.h"
#include "UGRC_DataAsset_HeroStartupData.generated.h"

USTRUCT(BlueprintType)
struct FUGRC_HeroAbilitySet
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUGRC_GameplayAbility> AbilityToGrant;
	
	bool IsValid() const;
};

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_DataAsset_HeroStartupData : public UUGRC_DataAsset_StartupDataBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(TObjectPtr<UUGRC_AbilitySystemComponent> InASCToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData", meta = (TitleProperty = "InputTag"))
	TArray<FUGRC_HeroAbilitySet> HeroStartupAbilitySets;
};