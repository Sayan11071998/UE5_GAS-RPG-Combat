#pragma once

#include "CoreMinimal.h"
#include "UGRC_EnumTypes.generated.h"

UENUM()
enum class EUGRC_ConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EUGRC_ValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EUGRC_SuccessType : uint8
{
	Successful,
	Failed
};

UENUM()
enum class EUGRC_CountDownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class EUGRC_CountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};
