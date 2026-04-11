#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/UGRC_PickUpBase.h"
#include "UGRC_StoneBase.generated.h"

class UGameplayEffect;
class UUGRC_AbilitySystemComponent;

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_StoneBase : public AUGRC_PickUpBase
{
	GENERATED_BODY()
	
public:
	void Consume(UUGRC_AbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);
	
protected:
	virtual void OnPickUpCollisionSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult	
	) override;
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Stone Consumed"))
	void BP_OnStoneConsumed();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> StoneGameplayEffectClass;
};