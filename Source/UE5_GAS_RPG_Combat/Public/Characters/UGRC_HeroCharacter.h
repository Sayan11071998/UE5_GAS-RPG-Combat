#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Characters/UGRC_BaseCharacter.h"
#include "UGRC_HeroCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UUGRC_HeroCombatComponent;
class UUGRC_DataAsset_InputConfig;
class UUGRC_HeroUIComponent;
struct FInputActionValue;

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_HeroCharacter : public AUGRC_BaseCharacter
{
	GENERATED_BODY()
	
public:
	AUGRC_HeroCharacter();
	
	// ~ Begin IUGRC_PawnCombatInterface Interface
	virtual TObjectPtr<UUGRC_PawnCombatComponent> GetPawnCombatComponent() const override;
	// ~ End IUGRC_PawnCombatInterface Interface
	
	// ~ Begin IUGRC_PawnUIInterface Interface
	virtual TObjectPtr<UUGRC_PawnUIComponent> GetPawnUIComponent() const override;
	// ~ End IUGRC_PawnUIInterface Interface
	
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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUGRC_HeroCombatComponent> HeroCombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUGRC_HeroUIComponent> HeroUIComponent;
#pragma endregion
	
#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUGRC_DataAsset_InputConfig> InputConfigDataAsset;
	
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	
	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
#pragma endregion
	
public:
	FORCEINLINE TObjectPtr<UUGRC_HeroCombatComponent> GetHeroCombatComponent() const { return HeroCombatComponent; }
};