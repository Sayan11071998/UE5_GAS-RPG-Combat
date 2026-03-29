#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "UGRC_HeroController.generated.h"

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_HeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	AUGRC_HeroController();
	
	// ~ Begin IGenericTeamAgentInterface Interface
	virtual FGenericTeamId GetGenericTeamId() const override;
	// ~ End IGenericTeamAgentInterface Interface
	
private:
	FGenericTeamId HeroTeamID;
};