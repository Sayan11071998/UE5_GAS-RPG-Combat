#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "UGRC_BaseCharacter.generated.h"

class UUGRC_AbilitySystemComponent;
class UUGRC_AttributeSet;

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AUGRC_BaseCharacter();
	
	// ~ Begin IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ~ End IAbilitySystemInterface Interface
	
protected:
	// ~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	// ~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UUGRC_AbilitySystemComponent> UGRC_AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UUGRC_AttributeSet> UGRC_AttributeSet;
	
public:
	FORCEINLINE TObjectPtr<UUGRC_AbilitySystemComponent> GetUUGRC_AbilitySystemComponent() const { return UGRC_AbilitySystemComponent; }
	FORCEINLINE TObjectPtr<UUGRC_AttributeSet> GetUUGRC_AttributeSet() const { return UGRC_AttributeSet; }
};