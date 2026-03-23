#pragma once

#include "CoreMinimal.h"
#include "Characters/UGRC_BaseCharacter.h"
#include "UGRC_HeroCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UUGRC_DataAsset_InputConfig;
struct FInputActionValue;

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_HeroCharacter : public AUGRC_BaseCharacter
{
	GENERATED_BODY()
	
public:
	AUGRC_HeroCharacter();
	
protected:
	// ~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	// ~ End APawn Interface
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	
private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
#pragma endregion
	
#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUGRC_DataAsset_InputConfig> InputConfigDataAsset;
	
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
#pragma endregion
};