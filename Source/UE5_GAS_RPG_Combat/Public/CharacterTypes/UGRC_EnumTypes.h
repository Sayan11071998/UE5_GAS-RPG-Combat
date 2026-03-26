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