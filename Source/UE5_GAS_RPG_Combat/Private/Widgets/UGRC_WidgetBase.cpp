#include "Widgets/UGRC_WidgetBase.h"
#include "Interfaces/UGRC_PawnUIInterface.h"

void UUGRC_WidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (IUGRC_PawnUIInterface* PawnUIInterface = Cast<IUGRC_PawnUIInterface>(OwningEnemyActor))
	{
		UUGRC_EnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();
		checkf(EnemyUIComponent, TEXT("Failed to extract an EnemyUIComponent from %s"), *OwningEnemyActor->GetActorNameOrLabel());
		
		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}

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