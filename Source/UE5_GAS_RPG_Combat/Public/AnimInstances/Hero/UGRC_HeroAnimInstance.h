#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/UGRC_CharacterAnimInstance.h"
#include "UGRC_HeroAnimInstance.generated.h"

class AUGRC_HeroCharacter;

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_HeroAnimInstance : public UUGRC_CharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	// ~ Begin UAnimInstance interface
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	// ~ End UAnimInstance interface
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|References")
	TObjectPtr<AUGRC_HeroCharacter> OwningHeroCharacter;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.f;

	float IdleElapsedTime;
};