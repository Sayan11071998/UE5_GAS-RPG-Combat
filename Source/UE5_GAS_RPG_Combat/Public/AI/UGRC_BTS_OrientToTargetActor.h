#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "UGRC_BTS_OrientToTargetActor.generated.h"

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_BTS_OrientToTargetActor : public UBTService
{
	GENERATED_BODY()

	UUGRC_BTS_OrientToTargetActor();
	
	// ~ Begin UBTNode Interface
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;
	// ~ End UBTNode Interface
	
	// ~ Begin UBTService Interface
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	// ~ End UBTService Interface
	
	UPROPERTY(EditAnywhere, Category = "Target")
	FBlackboardKeySelector InTargetActorKey;
	
	UPROPERTY(EditAnywhere, Category = "Target")
	float RotationInterpSpeed;
};