#include "UGRC_FunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/UGRC_AbilitySystemComponent.h"
#include "Interfaces/UGRC_PawnCombatInterface.h"

TObjectPtr<UUGRC_AbilitySystemComponent> UUGRC_FunctionLibrary::NativeGetWarriorASCFromActor(TObjectPtr<AActor> InActor)
{
	check(InActor);
	
	return CastChecked<UUGRC_AbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

bool UUGRC_FunctionLibrary::NativeDoesActorHaveTag(TObjectPtr<AActor> InActor, FGameplayTag TagToCheck)
{
	UUGRC_AbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);
	
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

TObjectPtr<UUGRC_PawnCombatComponent> UUGRC_FunctionLibrary::NativeGetPawnCombatComponentFromActor(
	TObjectPtr<AActor> InActor)
{
	check(InActor);
	
	if (IUGRC_PawnCombatInterface* PawnCombatInterface = Cast<IUGRC_PawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}
	
	return nullptr;
}

void UUGRC_FunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UUGRC_AbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);
	
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UUGRC_FunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UUGRC_AbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);
	
	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

void UUGRC_FunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck,
	EUGRC_ConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EUGRC_ConfirmType::Yes : EUGRC_ConfirmType::No;
}

UUGRC_PawnCombatComponent* UUGRC_FunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
	EUGRC_ValidType& OutValidType)
{
	UUGRC_PawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
	
	OutValidType = CombatComponent ? EUGRC_ValidType::Valid : EUGRC_ValidType::Invalid;
	
	return CombatComponent;
}