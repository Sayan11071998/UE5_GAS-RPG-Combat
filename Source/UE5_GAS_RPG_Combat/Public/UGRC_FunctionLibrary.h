#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CharacterTypes/UGRC_EnumTypes.h"
#include "UGRC_FunctionLibrary.generated.h"

class UUGRC_AbilitySystemComponent;
class UUGRC_PawnCombatComponent;
struct FScalableFloat;
struct FGameplayEffectSpecHandle;

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static TObjectPtr<UUGRC_AbilitySystemComponent> NativeGetWarriorASCFromActor(TObjectPtr<AActor> InActor);
	static bool NativeDoesActorHaveTag(TObjectPtr<AActor> InActor, FGameplayTag TagToCheck);
	static TObjectPtr<UUGRC_PawnCombatComponent> NativeGetPawnCombatComponentFromActor(TObjectPtr<AActor> InActor);
	
	UFUNCTION(BlueprintCallable, Category = "UGRC|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);
	
	UFUNCTION(BlueprintCallable, Category = "UGRC|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);
	
	UFUNCTION(BlueprintCallable, Category = "UGRC|FunctionLibrary", meta =(DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EUGRC_ConfirmType& OutConfirmType);
	
	UFUNCTION(BlueprintCallable, Category = "UGRC|FunctionLibrary", meta =(DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UUGRC_PawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EUGRC_ValidType& OutValidType);
	
	UFUNCTION(BlueprintPure, Category = "UGRC|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);
	
	UFUNCTION(BlueprintPure, Category = "UGRC|FunctionLibrary", meta = (CompactNodeTitle = "Get Value at Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);
	
	UFUNCTION(BlueprintPure, Category = "UGRC|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);
	
	UFUNCTION(BlueprintPure, Category = "UGRC|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);
	
	UFUNCTION(BlueprintCallable, Category = "UGRC|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);
};