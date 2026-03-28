#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UGRC_WidgetBase.generated.h"

class UUGRC_HeroUIComponent;

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_WidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// ~ Begin UUserWidget Interface
	virtual void NativeOnInitialized() override;
	// ~ End UUserWidget Interface
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Hero UI Component Initialized"))
	void BP_OnOwningHeroUIComponentInitialized(UUGRC_HeroUIComponent* OwningHeroUIComponent);
};