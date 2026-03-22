#pragma once

#include "CoreMinimal.h"
#include "Characters/UGRC_BaseCharacter.h"
#include "UGRC_HeroCharacter.generated.h"

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_HeroCharacter : public AUGRC_BaseCharacter
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};