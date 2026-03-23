#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/UGRC_BaseAnimInstance.h"
#include "UGRC_CharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AUGRC_BaseCharacter;

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_CharacterAnimInstance : public UUGRC_BaseAnimInstance
{
	GENERATED_BODY()
	
public:
	// ~ Begin UAnimInstance interface
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	// ~ End UAnimInstance interface
	
protected:
	UPROPERTY()
	TObjectPtr<AUGRC_BaseCharacter> OwningCharacter;
	
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwningMovementComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;
};