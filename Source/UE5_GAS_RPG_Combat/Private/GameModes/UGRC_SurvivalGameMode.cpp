#include "GameModes/UGRC_SurvivalGameMode.h"
#include "Engine/AssetManager.h"
#include "Characters/UGRC_EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "NavigationSystem.h"

#include "UGRC_DebugHelper.h"

void AUGRC_SurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(EnemyWaveSpawnerDataTable, TEXT("Forgot to assign a valid data table in survival game mode blueprint"));
	
	SetCurrentSurvivalGameModeState(EUGRC_SurvivalGameModeState::WaitSpawnNewWave);
	
	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();
	
	PreLoadNextWaveEnemies();
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
			CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
			
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
				PreLoadNextWaveEnemies();
			}
		}
	}
}

void AUGRC_SurvivalGameMode::RegisterSpawnedEnemies(const TArray<AUGRC_EnemyCharacter*>& InEnemiesToRegister)
{
	for (AUGRC_EnemyCharacter* SpawnedEnemy : InEnemiesToRegister)
	{
		if (SpawnedEnemy)
		{
			CurrentSpawnedEnemiesCounter++;
			SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &AUGRC_SurvivalGameMode::OnEnemyDestroyed);
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

void AUGRC_SurvivalGameMode::PreLoadNextWaveEnemies()
{
	if (HasFinishedAllWaves()) return;
	
	PreLoadedEnemyClassMap.Empty();
	
	for (const FUGRC_EnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;
		
		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[SpawnerInfo, this]()
				{
					if (UClass* LoadedEnemyClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
					{
						PreLoadedEnemyClassMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, LoadedEnemyClass);
					}
				}
			)
		);
	}
}

FUGRC_EnemyWaveSpawnerTableRow* AUGRC_SurvivalGameMode::GetCurrentWaveSpawnerTableRow() const
{
	const FName RowName = FName(TEXT("Wave") + FString::FromInt(CurrentWaveCount));
	
	FUGRC_EnemyWaveSpawnerTableRow* FoundRow = EnemyWaveSpawnerDataTable->FindRow<FUGRC_EnemyWaveSpawnerTableRow>(RowName, FString());
	checkf(FoundRow, TEXT("Could not find valid Row under the name %s in the data table"), *RowName.ToString());
	
	return FoundRow;
}

int32 AUGRC_SurvivalGameMode::TrySpawnWaveEnemies()
{
	if (TargetPointsArray.IsEmpty())
	{
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), TargetPointsArray);
	}
	
	checkf(!TargetPointsArray.IsEmpty(), TEXT("No valid target point found in level %s for spawning enemies"), *GetWorld()->GetName());

	uint32 EnemiesSpawnedThisTime = 0;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	for (const FUGRC_EnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;
		
		const int32 NumToSpawn = FMath::RandRange(SpawnerInfo.MinPerSpawnCount, SpawnerInfo.MaxPerSpawnCount);
		UClass* LoadedEnemyClass = PreLoadedEnemyClassMap.FindChecked(SpawnerInfo.SoftEnemyClassToSpawn);
		
		for (int32 i = 0; i < NumToSpawn; i++)
		{
			const int32 RandomTargetPointIndex = FMath::RandRange(0, TargetPointsArray.Num() - 1);
			const FVector SpawnOrigin = TargetPointsArray[RandomTargetPointIndex]->GetActorLocation();
			const FRotator SpawnRotation = TargetPointsArray[RandomTargetPointIndex]->GetActorForwardVector().ToOrientationRotator();
			
			FVector RandomLocation;
			
			UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, SpawnOrigin, RandomLocation, 400.f);
			RandomLocation += FVector(0.f, 0.f, 150.f);
			
			AUGRC_EnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<AUGRC_EnemyCharacter>(LoadedEnemyClass, RandomLocation, SpawnRotation, SpawnParams);
		
			if (SpawnedEnemy)
			{
				SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &AUGRC_SurvivalGameMode::OnEnemyDestroyed);
				
				EnemiesSpawnedThisTime++;
				TotalSpawnedEnemiesThisWaveCounter++;
			}
			
			if (ShouldKeepSpawnEnemies()) return EnemiesSpawnedThisTime;
		}
	}
	
	return EnemiesSpawnedThisTime;
}

bool AUGRC_SurvivalGameMode::ShouldKeepSpawnEnemies() const
{
	return TotalSpawnedEnemiesThisWaveCounter < GetCurrentWaveSpawnerTableRow()->TotalEnemyToSpawnThisWave;
}

void AUGRC_SurvivalGameMode::OnEnemyDestroyed(AActor* DestroyedActor)
{
	CurrentSpawnedEnemiesCounter--;
	
	Debug::Print(FString::Printf(TEXT("CurrentSpawnedEnemiesCounter: %i, TotalSpawnedEnemiesThisWaveCounter: %i"), CurrentSpawnedEnemiesCounter, TotalSpawnedEnemiesThisWaveCounter));
	
	if (ShouldKeepSpawnEnemies())
	{
		CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
	}
	else if (CurrentSpawnedEnemiesCounter == 0)
	{
		TotalSpawnedEnemiesThisWaveCounter = 0;
		CurrentSpawnedEnemiesCounter = 0;
		
		SetCurrentSurvivalGameModeState(EUGRC_SurvivalGameModeState::WaveCompleted);
	}
}