#include "AnimInstances/UGRC_CharacterAnimInstance.h"
#include "Characters/UGRC_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UUGRC_CharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AUGRC_BaseCharacter>(TryGetPawnOwner());
	
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UUGRC_CharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent) return;
	
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}