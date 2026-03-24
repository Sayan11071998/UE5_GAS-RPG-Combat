#include "AnimInstances/Hero/UGRC_HeroLinkedAnimLayer.h"
#include "AnimInstances/UGRC_CharacterAnimInstance.h"

UUGRC_CharacterAnimInstance* UUGRC_HeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UUGRC_CharacterAnimInstance>(GetOwningComponent()->GetAnimInstance());
}