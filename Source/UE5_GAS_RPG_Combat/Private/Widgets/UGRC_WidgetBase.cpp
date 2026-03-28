#include "Widgets/UGRC_WidgetBase.h"
#include "Interfaces/UGRC_PawnUIInterface.h"

void UUGRC_WidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (IUGRC_PawnUIInterface* PawnUIInterface = Cast<IUGRC_PawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UUGRC_HeroUIComponent* HeroUIComponent = PawnUIInterface->GetHeroUIComponent())
		{
			BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
		}
	}
}