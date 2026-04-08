#include "Components/Combat/UGRC_EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "UGRC_GameplayTags.h"
#include "UGRC_FunctionLibrary.h"
#include "Characters/UGRC_EnemyCharacter.h"
#include "Components/BoxComponent.h"

void UUGRC_EnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;
	
	OverlappedActors.Add(HitActor);
	
	bool bIsValidBlock = false;
	
	const bool bIsPlayerBlocking = UUGRC_FunctionLibrary::NativeDoesActorHaveTag(HitActor, UGRC_GameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = UUGRC_FunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), UGRC_GameplayTags::Enemy_Status_Unblockable);
	
	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UUGRC_FunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}
	
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;
	
	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			UGRC_GameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			UGRC_GameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}

void UUGRC_EnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable,
	EUGRC_ToggleDamageType ToggleDamageType)
{
	AUGRC_EnemyCharacter* OwningEnemyCharacter = GetOwningPawn<AUGRC_EnemyCharacter>();
	check(OwningEnemyCharacter);
	
	UBoxComponent* LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollisionBox();
	
	check(LeftHandCollisionBox && RightHandCollisionBox);

	switch (ToggleDamageType)
	{
	case EUGRC_ToggleDamageType::LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
		
	case EUGRC_ToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
		
	default:
		break;
	}
	
	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}