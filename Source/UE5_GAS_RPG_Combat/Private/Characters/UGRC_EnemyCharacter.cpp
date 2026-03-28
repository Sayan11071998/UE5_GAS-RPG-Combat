#include "Characters/UGRC_EnemyCharacter.h"
#include "Components/Combat/UGRC_EnemyCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartupData/UGRC_DataAsset_EnemyStartupData.h"
#include "Components/UI/UGRC_EnemyUIComponent.h"

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
	EnemyUIComponent = CreateDefaultSubobject<UUGRC_EnemyUIComponent>(TEXT("EnemyUIComponent"));
}

TObjectPtr<UUGRC_PawnCombatComponent> AUGRC_EnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

TObjectPtr<UUGRC_PawnUIComponent> AUGRC_EnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

void AUGRC_EnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitEnemyStartupData();
}

void AUGRC_EnemyCharacter::InitEnemyStartupData()
{
	if (CharacterStartupData.IsNull()) return;
	
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartupData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UUGRC_DataAsset_StartupDataBase* LoadedData = CharacterStartupData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(UGRC_AbilitySystemComponent);
				}
			}
		)
	);
}