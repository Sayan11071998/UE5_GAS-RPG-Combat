#include "AbilitySystem/GEExecCalc/UGRC_GEExecCalc_DamageTaken.h"
#include "AbilitySystem/UGRC_AttributeSet.h"
#include "UGRC_GameplayTags.h"

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

void UUGRC_GEExecCalc_DamageTaken::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	
	// EffectSpec.GetContext().GetSourceObject();
	// EffectSpec.GetContext().GetAbility();
	// EffectSpec.GetContext().GetInstigator();
	// EffectSpec.GetContext().GetEffectCauser();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();
	
	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		GetUGRCDamageCapture().AttackPowerDef,
		EvaluateParameters,
		SourceAttackPower
	);
	
	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;
	
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(UGRC_GameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}
		
		if (TagMagnitude.Key.MatchesTagExact(UGRC_GameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
		}
		
		if (TagMagnitude.Key.MatchesTagExact(UGRC_GameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
		}
	}
	
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		GetUGRCDamageCapture().DefensePowerDef,
		EvaluateParameters,
		TargetDefensePower
	);
}