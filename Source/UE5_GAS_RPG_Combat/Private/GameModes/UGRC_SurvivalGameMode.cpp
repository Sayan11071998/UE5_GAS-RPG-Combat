#include "GameModes/UGRC_SurvivalGameMode.h"

void AUGRC_SurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(EnemyWaveSpawnerDataTable, TEXT("Forgot to assign a valid data table in survival game mode blueprint"));
	
	SetCurrentSurvivalGameModeState(EUGRC_SurvivalGameModeState::WaitSpawnNewWave);
	
	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();
}

void AUGRC_SurvivalGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (CurrentSurvivalGameModeState == EUGRC_SurvivalGameModeState::WaitSpawnNewWave)
	{
		TimePassedSinceStart += DeltaTime;
		
		if (TimePassedSinceStart >= SpawnNewWaveWaitTime)
		{
			TimePassedSinceStart = 0.f;
			SetCurrentSurvivalGameModeState(EUGRC_SurvivalGameModeState::SpawningNewWave);
		}
	}
	
	if (CurrentSurvivalGameModeState == EUGRC_SurvivalGameModeState::SpawningNewWave)
	{
		TimePassedSinceStart += DeltaTime;
		
		if (TimePassedSinceStart >= SpawnEnemiesDelayTime)
		{
			// TODO: Handle Spawn New Enemies
			
			TimePassedSinceStart = 0.f;
			SetCurrentSurvivalGameModeState(EUGRC_SurvivalGameModeState::InProgress);
		}
	}
	
	if (CurrentSurvivalGameModeState == EUGRC_SurvivalGameModeState::WaveCompleted)
	{
		TimePassedSinceStart += DeltaTime;
		
		if (TimePassedSinceStart >= WaveCompletedWaitTime)
		{
			TimePassedSinceStart = 0.f;
			CurrentWaveCount++;
			
			if (HasFinishedAllWaves())
			{
				SetCurrentSurvivalGameModeState(EUGRC_SurvivalGameModeState::AllWavesDone);
			}
			else
			{
				SetCurrentSurvivalGameModeState(EUGRC_SurvivalGameModeState::WaitSpawnNewWave);
			}
		}
	}
}

void AUGRC_SurvivalGameMode::SetCurrentSurvivalGameModeState(EUGRC_SurvivalGameModeState InState)
{
	CurrentSurvivalGameModeState = InState;
	OnSurvivalGameModeStateChanged.Broadcast(CurrentSurvivalGameModeState);
}

bool AUGRC_SurvivalGameMode::HasFinishedAllWaves() const
{
	return CurrentWaveCount > TotalWavesToSpawn;
}