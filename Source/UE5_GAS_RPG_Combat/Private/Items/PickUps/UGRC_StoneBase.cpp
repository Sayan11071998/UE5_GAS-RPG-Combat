#include "Items/PickUps/UGRC_StoneBase.h"
#include "Characters/UGRC_HeroCharacter.h"
#include "AbilitySystem/UGRC_AbilitySystemComponent.h"
#include "UGRC_GameplayTags.h"

void AUGRC_StoneBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AUGRC_HeroCharacter* OverlappedHeroCharacter = Cast<AUGRC_HeroCharacter>(OtherActor))
	{
		OverlappedHeroCharacter->GetUGRC_AbilitySystemComponent()->TryActivateAbilityTag(UGRC_GameplayTags::Player_Ability_PickUp_Stones);
	}
}