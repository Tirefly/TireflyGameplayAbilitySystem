// Copyright Tirefly. All Rights Reserved.


#include "Attribute/TireflyAttributeInstance.h"

#include "TireflyGameplayAbilitySystemComponent.h"
#include "TireflyGameplayAbilitySystemLogChannel.h"
#include "Attribute/TireflyAttributeDefinition.h"
#include "Calculator/TireflyAttributeEvaluator.h"


bool FTireflyAttributeInstance::IsValid() const
{
	return Definition != nullptr && Owner != nullptr;
}

FName FTireflyAttributeInstance::GetAttributeName() const
{
	if (!Definition)
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Attribute definition is not set"), *FString(__FUNCTION__));
		return NAME_None;
	}
	
	return Definition->GetGameplayAttributeNameDefine();
}

FString FTireflyAttributeInstance::DebugString() const
{
	return FString::Printf(TEXT("Attribute: %s, BaseValue: %f, CurrentValue: %f"),
		*GetAttributeName().ToString(), BaseValue, CurrentValue);
}

FText FTireflyAttributeInstance::GetShowcaseForUI() const
{
	if (!Definition)
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Attribute definition is not set"), *FString(__FUNCTION__));
		return FText::FromString(TEXT("Invalid Attribute"));
	}
	
	FString Showcase = Definition->IsAsDecimal()
		? FString::Printf(TEXT("%.2f"), CurrentValue)
		: FString::FromInt(FMath::RoundToInt(CurrentValue));
	if (Definition->IsAsPercentage())
	{
		Showcase += TEXT("%");
	}

	return FText::FromString(Showcase);
}

float FTireflyAttributeInstance::ClampAttributeValue(float InValue) const
{
	if (!Definition)
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Attribute 's definition is not set"), *FString(__FUNCTION__));
		return InValue;
	}

	if (!Owner)
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Owner of {%s} is not set"),
			*FString(__FUNCTION__), *Definition->GetGameplayAttributeName().ToString());
		return InValue;
	}
	
	const FTireflyAttributeRange& Range = Definition->GetAttributeRange();

	// 如果没有设置最小值和最大值，则直接返回原值
	if (!Range.bHasMinValue && !Range.bHasMaxValue)
	{
		return InValue;
	}

	float MinValue = InValue;
	float MaxValue = InValue;
    
	// Handle MinValue
	if (Range.bHasMinValue)
	{
		if (Range.bMinValueUseAttribute)
		{
			if (!Range.MinValueAttribute.IsValid())
			{
				UE_LOG(LogTireflyAttribute, Warning, TEXT("[%s] MinValueAttribute of {%s} is invalid, using default value"),
					*FString(__FUNCTION__), *Definition->GetGameplayAttributeName().ToString());
				MinValue = static_cast<float>(INT_MIN);
			}
			else
			{
				if (!Owner->GetAttributeValue(Range.MinValueAttribute, MinValue))
				{
					UE_LOG(LogTireflyAttribute, Warning, TEXT("[%s] Failed to get MinValueAttribute of {%s}, using default value"),
						*FString(__FUNCTION__), *Definition->GetGameplayAttributeName().ToString());
					MinValue = static_cast<float>(INT_MIN);
				 }
			}
		}
		else
		{
			MinValue = Range.MinValue;
		}
	}

	// Handle MaxValue
	if (Range.bHasMaxValue)
	{
		if (Range.bMaxValueUseAttribute)
		{
			if (!Range.MaxValueAttribute.IsValid())
			{
				UE_LOG(LogTireflyAttribute, Warning, TEXT("[%s] MaxValueAttribute of {%s} is invalid, using default value"),
					*FString(__FUNCTION__), *Definition->GetGameplayAttributeName().ToString());
				MaxValue = static_cast<float>(INT_MAX);
			}
			else
			{
				if (!Owner->GetAttributeValue(Range.MaxValueAttribute, MaxValue))
				{
					UE_LOG(LogTireflyAttribute, Warning, TEXT("[%s] Failed to get MaxValueAttribute of {%s}, using default value"),
						*FString(__FUNCTION__), *Definition->GetGameplayAttributeName().ToString());
					MaxValue = static_cast<float>(INT_MAX);
				}
			}
		}
		else
		{
			MaxValue = Range.MaxValue;
		}
	}

	// Ensure MinValue <= MaxValue
	if (MinValue > MaxValue)
	{
		UE_LOG(LogTireflyAttribute, Warning, TEXT("[%s] {%s} MinValue (%f) is greater than MaxValue (%f), clamping to MaxValue"),
			*FString(__FUNCTION__), *Definition->GetGameplayAttributeName().ToString(), MinValue, MaxValue);
		MinValue = MaxValue;
	}

	return FMath::Clamp(InValue, MinValue, MaxValue);
}

void FTireflyAttributeInstance::AddModifier(const FTireflyAttributeModifierInstance& Modifier)
{
	if (!Modifier.IsValid())
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Modifier {%s} is invalid"),
			*FString(__FUNCTION__), *Modifier.DebugString());
		return;
	}

	Modifiers.Add(Modifier.Handle, Modifier);
	UpdateCurrentValue();
}

void FTireflyAttributeInstance::RemoveModifier(const FTireflyAttributeModifierInstance& Modifier)
{
	if (!Modifier.IsValid())
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Modifier {%s} is invalid"),
			*FString(__FUNCTION__), *Modifier.DebugString());
		return;
	}
	RemoveModifier(Modifier.Handle);
}

void FTireflyAttributeInstance::RemoveModifier(int32 ModifierHandle)
{
	if (!Modifiers.Contains(ModifierHandle))
	{
		return;
	}

	Modifiers.Remove(ModifierHandle);
	UpdateCurrentValue();
}

void FTireflyAttributeInstance::SetBaseValue(float NewBaseValue)
{
	if (!Definition)
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Attribute definition is not set"), *FString(__FUNCTION__));
		return;
	}

	if (!Owner)
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Owner of {%s} is not set"),
			*FString(__FUNCTION__), *Definition->GetGameplayAttributeName().ToString());
		return;
	}
	
	BaseValue = ClampAttributeValue(NewBaseValue);
	Owner->HandleAttributeBaseValueChanged(*this);
	
	UpdateCurrentValue();
}

void FTireflyAttributeInstance::UpdateCurrentValue()
{
	CurrentValue = ClampAttributeValue(Definition->GetAttributeEvaluator()->EvaluateCurrentValue(BaseValue, Modifiers));
	Owner->HandleAttributeValueChanged(*this);
}
