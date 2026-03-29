#include "Controllers/UGRC_AIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "UGRC_DebugHelper.h"

AUGRC_AIController::AUGRC_AIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	if (UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		Debug::Print(TEXT("UCrowdFollowingComponent valid"));
	}
	
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("EnemySenseConfig_Sight"));
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	AISenseConfig_Sight->SightRadius = 5000.f;
	AISenseConfig_Sight->LoseSightRadius = 0.f;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;
	
	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent"));
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AUGRC_AIController::OnEnemyPerceptionUpdated);
}

void AUGRC_AIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
}