#include "Components/UI/UGRC_EnemyUIComponent.h"
#include "Widgets/UGRC_WidgetBase.h"

void UUGRC_EnemyUIComponent::RegisterEnemyDrawnWidget(UUGRC_WidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UUGRC_EnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if (EnemyDrawnWidgets.IsEmpty()) return;
	
	for (UUGRC_WidgetBase* DrawnWidget : EnemyDrawnWidgets)
	{
		if (DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}
}