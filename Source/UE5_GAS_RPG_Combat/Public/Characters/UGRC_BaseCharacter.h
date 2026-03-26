#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/UGRC_PawnCombatInterface.h"
#include "UGRC_BaseCharacter.generated.h"

class UUGRC_AbilitySystemComponent;
class UUGRC_AttributeSet;
class UUGRC_DataAsset_StartupDataBase;

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_BaseCharacter : public ACharacter, public IAbilitySystemInterface, public IUGRC_PawnCombatInterface
{
	GENERATED_BODY()

public:
	AUGRC_BaseCharacter();
	
	// ~ Begin IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ~ End IAbilitySystemInterface Interface
	
	// ~ Begin IUGRC_PawnCombatInterface Interface
	virtual TObjectPtr<UUGRC_PawnCombatComponent> GetPawnCombatComponent() const override;
	// ~ End IUGRC_PawnCombatInterface Interface
	
protected:
	// ~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	// ~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UUGRC_AbilitySystemComponent> UGRC_AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UUGRC_AttributeSet> UGRC_AttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UUGRC_DataAsset_StartupDataBase> CharacterStartupData;
	
public:
	FORCEINLINE TObjectPtr<UUGRC_AbilitySystemComponent> GetUGRC_AbilitySystemComponent() const { return UGRC_AbilitySystemComponent; }
	FORCEINLINE TObjectPtr<UUGRC_AttributeSet> GetUGRC_AttributeSet() const { return UGRC_AttributeSet; }
};