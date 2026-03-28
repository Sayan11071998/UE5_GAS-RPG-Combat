#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "UGRC_GEExecCalc_DamageTaken.generated.h"

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_GEExecCalc_DamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UUGRC_GEExecCalc_DamageTaken();
	
	// ~ Begin UGameplayEffectExecutionCalculation Interface
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	// ~ End UGameplayEffectExecutionCalculation Interface
};