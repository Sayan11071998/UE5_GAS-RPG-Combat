#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UGRC_PawnUIInterface.generated.h"

class UUGRC_EnemyUIComponent;
class UUGRC_PawnUIComponent;
class UUGRC_HeroUIComponent;

UINTERFACE(MinimalAPI)
class UUGRC_PawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

class UE5_GAS_RPG_COMBAT_API IUGRC_PawnUIInterface
{
	GENERATED_BODY()
	
public:
	virtual TObjectPtr<UUGRC_PawnUIComponent> GetPawnUIComponent() const = 0;
	virtual TObjectPtr<UUGRC_HeroUIComponent> GetHeroUIComponent() const;
	virtual TObjectPtr<UUGRC_EnemyUIComponent> GetEnemyUIComponent() const;
};