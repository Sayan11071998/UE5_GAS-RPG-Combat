#pragma once

#include "CoreMinimal.h"
#include "GameModes/UGRC_GameModeBase.h"
#include "UGRC_SurvivalGameMode.generated.h"

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
	
	UPROPERTY()
	EUGRC_SurvivalGameModeState CurrentSurvivalGameModeState;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSurvivalGameModeStateChangedDelegate OnSurvivalGameModeStateChanged;
};