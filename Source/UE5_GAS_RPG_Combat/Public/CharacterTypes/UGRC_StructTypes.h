#pragma once

#include "UGRC_StructTypes.generated.h"

class UUGRC_HeroLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FUGRC_HeroWeaponData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUGRC_HeroLinkedAnimLayer> WeaponAnimLayerToLink;
};