#include "Characters/UGRC_EnemyCharacter.h"
#include "Components/Combat/UGRC_EnemyCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AUGRC_EnemyCharacter::AUGRC_EnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;
	
	EnemyCombatComponent = CreateDefaultSubobject<UUGRC_EnemyCombatComponent>(TEXT("EnemyCombatComponent"));
}