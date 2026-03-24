#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/UGRC_WeaponBase.h"
#include "CharacterTypes/UGRC_StructTypes.h"
#include "UGRC_HeroWeapon.generated.h"

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_HeroWeapon : public AUGRC_WeaponBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FUGRC_HeroWeaponData HeroWeaponData;
};