#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/UGRC_DataAsset_InputConfig.h"
#include "UGRC_InputComponent.generated.h"

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_InputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const TObjectPtr<UUGRC_DataAsset_InputConfig> InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject ContextObject, CallbackFunc Func);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const TObjectPtr<UUGRC_DataAsset_InputConfig> InInputConfig, TObjectPtr<UserObject> ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);
};

template <class UserObject, typename CallbackFunc>
void UUGRC_InputComponent::BindNativeInputAction(const TObjectPtr<UUGRC_DataAsset_InputConfig> InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input config data asset is null, can not proceed with binding"));
	
	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

template <class UserObject, typename CallbackFunc>
void UUGRC_InputComponent::BindAbilityInputAction(const TObjectPtr<UUGRC_DataAsset_InputConfig> InInputConfig,
	TObjectPtr<UserObject> ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	checkf(InInputConfig, TEXT("Input config data asset is null, can not proceed with binding"));
	
	for (const FUGRC_InputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) continue;;
		
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, AbilityInputActionConfig.InputTag);
	}
}