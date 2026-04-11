#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UGRC_PickUpBase.generated.h"

class USphereComponent;

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_PickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AUGRC_PickUpBase();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pick Up Interaction")
	TObjectPtr<USphereComponent> PickUpCollisionSphere;
	
	UFUNCTION()
	virtual void OnPickUpCollisionSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult	
	);
};