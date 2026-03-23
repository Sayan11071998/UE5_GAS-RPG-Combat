#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/UGRC_PawnExtensionComponentBase.h"
#include "UGRC_PawnCombatComponent.generated.h"

class AUGRC_WeaponBase;

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_PawnCombatComponent : public UUGRC_PawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UGRC|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AUGRC_WeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category = "UGRC|Combat")
	AUGRC_WeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;
	
	UPROPERTY(BlueprintReadWrite, Category = "UGRC|Combat")
	FGameplayTag CurrentEquippedWeaponTag;
	
	UFUNCTION(BlueprintCallable, Category = "UGRC|Combat")
	AUGRC_WeaponBase* GetCharacterCurrentEquippedWeapon() const;
	
private:
	UPROPERTY()
	TMap<FGameplayTag, AUGRC_WeaponBase*> CharacterCarriedWeaponMap;
};