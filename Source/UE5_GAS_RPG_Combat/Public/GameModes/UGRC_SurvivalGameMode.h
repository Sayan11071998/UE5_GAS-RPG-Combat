#pragma once

#include "CoreMinimal.h"
#include "GameModes/UGRC_GameModeBase.h"
#include "UGRC_SurvivalGameMode.generated.h"

class AUGRC_EnemyCharacter;

UENUM(BlueprintType)
enum class EUGRC_SurvivalGameModeState : uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveCompleted,
	AllWavesDone,
	PlayerDied
};

USTRUCT(BlueprintType)
struct FUGRC_EnemyWaveSpawnerInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AUGRC_EnemyCharacter> SoftEnemyClassToSpawn;
	
	UPROPERTY(EditAnywhere)
	int32 MinPerSpawnCount = 1;
	
	UPROPERTY(EditAnywhere)
	int32 MaxPerSpawnCount = 3;
};

USTRUCT(BlueprintType)
struct FUGRC_EnemyWaveSpawnerTableRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<FUGRC_EnemyWaveSpawnerInfo> EnemyWaveSpawnerDefinitions;
	
	UPROPERTY(EditAnywhere)
	int32 TotalEnemyToSpawnThisWave = 1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvivalGameModeStateChangedDelegate, EUGRC_SurvivalGameModeState, CurrentState);

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_SurvivalGameMode : public AUGRC_GameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	void SetCurrentSurvivalGameModeState(EUGRC_SurvivalGameModeState InState);
	bool HasFinishedAllWaves() const;
	
	UPROPERTY()
	EUGRC_SurvivalGameModeState CurrentSurvivalGameModeState;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSurvivalGameModeStateChangedDelegate OnSurvivalGameModeStateChanged;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Definition", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataTable> EnemyWaveSpawnerDataTable;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Wave Definition", meta = (AllowPrivateAccess = "true"))
	int32 TotalWavesToSpawn;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Wave Definition", meta = (AllowPrivateAccess = "true"))
	int32 CurrentWaveCount = 1;
	
	UPROPERTY()
	float TimePassedSinceStart = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Definition", meta = (AllowPrivateAccess = "true"))
	float SpawnNewWaveWaitTime = 5.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Definition", meta = (AllowPrivateAccess = "true"))
	float SpawnEnemiesDelayTime = 2.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Definition", meta = (AllowPrivateAccess = "true"))
	float WaveCompletedWaitTime = 5.f;
};