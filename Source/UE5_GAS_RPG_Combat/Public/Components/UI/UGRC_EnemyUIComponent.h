#pragma once

#include "CoreMinimal.h"
#include "Components/UI/UGRC_PawnUIComponent.h"
#include "UGRC_EnemyUIComponent.generated.h"

class UUGRC_WidgetBase;

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_EnemyUIComponent : public UUGRC_PawnUIComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(UUGRC_WidgetBase* InWidgetToRegister);
	
	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();
	
private:
	TArray<TObjectPtr<UUGRC_WidgetBase>> EnemyDrawnWidgets;
};