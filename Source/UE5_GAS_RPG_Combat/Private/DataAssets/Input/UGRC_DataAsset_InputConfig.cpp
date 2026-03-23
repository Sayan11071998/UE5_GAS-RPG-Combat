#include "DataAssets/Input/UGRC_DataAsset_InputConfig.h"

TObjectPtr<UInputAction> UUGRC_DataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FUGRC_InputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}
	
	return nullptr;
}