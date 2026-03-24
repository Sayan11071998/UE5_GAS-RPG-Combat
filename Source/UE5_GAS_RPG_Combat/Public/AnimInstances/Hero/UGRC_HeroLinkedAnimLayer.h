#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/UGRC_BaseAnimInstance.h"
#include "UGRC_HeroLinkedAnimLayer.generated.h"

class UUGRC_CharacterAnimInstance;

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_HeroLinkedAnimLayer : public UUGRC_BaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UUGRC_CharacterAnimInstance* GetHeroAnimInstance() const;
};