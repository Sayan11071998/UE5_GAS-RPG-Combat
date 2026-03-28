#include "AbilitySystem/GEExecCalc/UGRC_GEExecCalc_DamageTaken.h"
#include "AbilitySystem/UGRC_AttributeSet.h"
#include "UGRC_GameplayTags.h"

#include "UGRC_DebugHelper.h"

struct FUGRC_DamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)
	
	FUGRC_DamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UUGRC_AttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UUGRC_AttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UUGRC_AttributeSet, DamageTaken, Target, false)
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
	RelevantAttributesToCapture.Add(GetUGRCDamageCapture().DamageTakenDef);
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
	// Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);
	
	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;
	
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(UGRC_GameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			// Debug::Print(TEXT("BaseDamage"), BaseDamage);
		}
		
		if (TagMagnitude.Key.MatchesTagExact(UGRC_GameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			// Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);
		}
		
		if (TagMagnitude.Key.MatchesTagExact(UGRC_GameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			// Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
		}
	}
	
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		GetUGRCDamageCapture().DefensePowerDef,
		EvaluateParameters,
		TargetDefensePower
	);
	// Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);
	
	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05f + 1.f;
		BaseDamage *= DamageIncreasePercentLight;
		// Debug::Print(TEXT("ScaledBaseDamageLight"), BaseDamage);
	}
	
	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;
		BaseDamage *= DamageIncreasePercentHeavy;
		// Debug::Print(TEXT("ScaledBaseDamageHeavy"), BaseDamage);
	}
	
	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	// Debug::Print(TEXT("FinalDamageDone"), FinalDamageDone);
	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetUGRCDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)	
		);
	}
}