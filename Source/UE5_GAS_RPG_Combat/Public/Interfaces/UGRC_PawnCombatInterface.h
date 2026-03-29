#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UGRC_PawnCombatInterface.generated.h"

class UUGRC_PawnCombatComponent;

UINTERFACE(MinimalAPI)
class UUGRC_PawnCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class UE5_GAS_RPG_COMBAT_API IUGRC_PawnCombatInterface
{
	GENERATED_BODY()
	
public:
	virtual TObjectPtr<UUGRC_PawnCombatComponent> GetPawnCombatComponent() const = 0;
};