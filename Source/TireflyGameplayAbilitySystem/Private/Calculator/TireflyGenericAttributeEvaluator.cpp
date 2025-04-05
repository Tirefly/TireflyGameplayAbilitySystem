// Copyright Tirefly. All Rights Reserved.


#include "Calculator/TireflyGenericAttributeEvaluator.h"

#include "TireflyGameplayAbilitySystemLogChannel.h"


UTireflyGenericAttributeEvaluator::UTireflyGenericAttributeEvaluator(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	EvaluatorType = TEXT("Tirefly Generic Attribute Evaluator");
	ModifiersDefine = {
		TireflyGenericAttrModType::ModType_Add,
		TireflyGenericAttrModType::ModType_MultiplyAdditive,
		TireflyGenericAttrModType::ModType_MultiplyCompound,
		TireflyGenericAttrModType::ModType_Divide,
		TireflyGenericAttrModType::ModType_Override
	};
}

float UTireflyGenericAttributeEvaluator::EvaluateCurrentValue_Implementation(float BaseValue,
	const TMap<int32, FTireflyAttributeModifierInstance>& Modifiers) const
{
	float AddMods = 0.f;
	float MultiAdditiveMods = 1.f;
	float MultiCompoundMods = 1.f;
	float DivideMods = 0.f;
	FTireflyAttributeModifierInstance NewestOverrideMod;
	
	for (auto&& [Handle, Modifier] : Modifiers)
	{
		if (!Modifier.IsValid())
		{
			UE_LOG(LogTireflyAttribute, Warning, TEXT("[%s] Invalid modifier {%s} instance found."),
				*FString(__FUNCTION__), *Modifier.DebugString());
			continue;
		}
		
		if (Modifier.ModifierType == TireflyGenericAttrModType::ModType_Add)
		{
			AddMods += Modifier.Magnitude;
		}
		else if (Modifier.ModifierType == TireflyGenericAttrModType::ModType_MultiplyAdditive)
		{
			MultiAdditiveMods *= Modifier.Magnitude;
		}
		else if (Modifier.ModifierType == TireflyGenericAttrModType::ModType_MultiplyCompound)
		{
			MultiCompoundMods *= Modifier.Magnitude;
		}
		else if (Modifier.ModifierType == TireflyGenericAttrModType::ModType_Divide)
		{
			DivideMods += Modifier.Magnitude;
		}
		else if (Modifier.ModifierType == TireflyGenericAttrModType::ModType_Override)
		{
			if (Modifier.Timestamp > NewestOverrideMod.Timestamp)
			{
				NewestOverrideMod = Modifier;
			}
		}
	}

	if (NewestOverrideMod.IsValid())
	{
		return NewestOverrideMod.Magnitude;
	}

	if (FMath::IsNearlyZero(DivideMods))
	{
		UE_LOG(LogTireflyAttribute, Warning, TEXT("[%s] Division multiplier summation appears to 0.f."),
			*FString(__FUNCTION__));
		DivideMods = 1.f;
	}

	return (BaseValue + AddMods) * MultiAdditiveMods * MultiCompoundMods / DivideMods;
}
