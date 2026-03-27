#include "AbilitySystem/GEExecCalc/UGRC_GEExecCalc_DamageTaken.h"
#include "AbilitySystem/UGRC_AttributeSet.h"

struct FUGRC_DamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	
	FUGRC_DamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UUGRC_AttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UUGRC_AttributeSet, DefensePower, Target, false)
	}
};

static const FUGRC_DamageCapture& GetUGRCDamageCapture()
{
	static FUGRC_DamageCapture UGRCDamageCapture;
	return UGRCDamageCapture;
}

UUGRC_GEExecCalc_DamageTaken::UUGRC_GEExecCalc_DamageTaken()
{
	/* Slow way of doing capture */
	// FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	// 	UUGRC_AttributeSet::StaticClass(),
	// 	GET_MEMBER_NAME_CHECKED(UUGRC_AttributeSet, AttackPower)
	// );
	//
	// FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
	// 	AttackPowerProperty,
	// 	EGameplayEffectAttributeCaptureSource::Source,
	// 	false
	// );
	//
	// RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);
	
	RelevantAttributesToCapture.Add(GetUGRCDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetUGRCDamageCapture().DefensePowerDef);
}