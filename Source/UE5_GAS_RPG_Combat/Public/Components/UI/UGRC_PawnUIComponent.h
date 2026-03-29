#pragma once

#include "CoreMinimal.h"
#include "Components/UGRC_PawnExtensionComponentBase.h"
#include "UGRC_PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangedDelegate, float, NewPercent);

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_PawnUIComponent : public UUGRC_PawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentHealthChanged;
};