#include "AbilitySystem/UGRC_AttributeSet.h"

UUGRC_AttributeSet::UUGRC_AttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}