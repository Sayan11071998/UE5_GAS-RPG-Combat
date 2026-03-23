#include "Characters/UGRC_BaseCharacter.h"
#include "AbilitySystem/UGRC_AbilitySystemComponent.h"
#include "AbilitySystem/UGRC_AttributeSet.h"

AUGRC_BaseCharacter::AUGRC_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	GetMesh()->bReceivesDecals = false;
	
	UGRC_AbilitySystemComponent = CreateDefaultSubobject<UUGRC_AbilitySystemComponent>(TEXT("UGRC_AbilitySystemComponent"));
	UGRC_AttributeSet = CreateDefaultSubobject<UUGRC_AttributeSet>(TEXT("UGRC_AttributeSet"));
}

UAbilitySystemComponent* AUGRC_BaseCharacter::GetAbilitySystemComponent() const
{
	return GetUGRC_AbilitySystemComponent();
}

void AUGRC_BaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (UGRC_AbilitySystemComponent)
	{
		UGRC_AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}