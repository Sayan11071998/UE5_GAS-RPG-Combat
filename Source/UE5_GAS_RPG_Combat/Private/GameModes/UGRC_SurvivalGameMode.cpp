#include "GameModes/UGRC_SurvivalGameMode.h"

void AUGRC_SurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AUGRC_SurvivalGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUGRC_SurvivalGameMode::SetCurrentSurvivalGameModeState(EUGRC_SurvivalGameModeState InState)
{
	CurrentSurvivalGameModeState = InState;
	OnSurvivalGameModeStateChanged.Broadcast(CurrentSurvivalGameModeState);
}