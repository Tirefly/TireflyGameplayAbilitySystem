// Copyright Tirefly. All Rights Reserved.


#include "Attribute/TireflyAttributeInstance.h"

#include "TireflyGameplayAbilitySystemComponent.h"
#include "TireflyGameplayAbilitySystemLogChannel.h"
#include "Attribute/TireflyAttributeDefinition.h"
#include "Calculator/TireflyAttributeEvaluator.h"


FTireflyAttributeInstance::FTireflyAttributeInstance(UTireflyAttributeDefinition* Def,
	UTireflyGameplayAbilitySystemComponent* InOwner, float InBaseValue)
{
	Definition = Def;
	Owner = InOwner;

	if (!Definition.IsValid())
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Attribute definition is not set"), *FString(__FUNCTION__));
		return;
	}
	
	AttributeName = Definition->GetGameplayAttributeNameDefine();
	SetBaseValue(InBaseValue);
}

FTireflyAttributeInstance::FTireflyAttributeInstance(const FTireflyAttributeInstance& Another)
{
	Definition = Another.Definition;
	Owner = Another.Owner;
	Modifiers = Another.Modifiers;

	if (!Definition.IsValid())
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Attribute definition is not set"), *FString(__FUNCTION__));
		return;
	}
	
	AttributeName = Definition->GetGameplayAttributeNameDefine();
		
	SetBaseValue(Another.BaseValue);
}

bool FTireflyAttributeInstance::IsValid() const
{
	return Definition != nullptr && Owner != nullptr;
}

FName FTireflyAttributeInstance::GetAttributeName() const
{
	return AttributeName;
}

FString FTireflyAttributeInstance::DebugString() const
{
	return FString::Printf(TEXT("Attribute: %s, BaseValue: %f, CurrentValue: %f"),
		*AttributeName.ToString(), BaseValue, CurrentValue);
}

FText FTireflyAttributeInstance::GetShowcaseForUI() const
{
	if (!Definition.IsValid())
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
	if (!Definition.IsValid())
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Attribute 's definition is not set"), *FString(__FUNCTION__));
		return InValue;
	}

	if (!Owner)
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Owner of {%s} is not set"),
			*FString(__FUNCTION__), *AttributeName.ToString());
		return InValue;
	}
	
	const FTireflyAttributeRange& Range = Definition->GetAttributeRange();

	// 如果没有设置最小值和最大值，则直接返回原值
	if (!Range.bHasMinValue && !Range.bHasMaxValue)
	{
		return InValue;
	}

	// Lambda函数用于处理最小值和最大值的获取
	auto GetBoundValue = [&, this](
		bool bHasBound,
		bool bUseAttribute,
		const FName& BoundAttribute,
		float InBoundValue,
		float DefaultValue)
	{
		if (!bHasBound)
		{
			return InValue;
		}

		if (bUseAttribute)
		{
			float BoundValue;
			if (!Owner->GetAttributeValue(BoundAttribute, BoundValue))
			{
				UE_LOG(LogTireflyAttribute, Warning, TEXT("[%s] Failed to get BoundAttribute of {%s}, using default value"),
					*FString(__FUNCTION__), *AttributeName.ToString());
				return DefaultValue;
			}
			return BoundValue;
		}
		else
		{
			return InBoundValue;
		}
	};

	float MinValue = GetBoundValue(Range.bHasMinValue, Range.bMinValueUseAttribute, Range.MinValueAttribute, Range.MinValue, -FLT_MIN);
	float MaxValue = GetBoundValue(Range.bHasMaxValue, Range.bMaxValueUseAttribute, Range.MaxValueAttribute, Range.MaxValue, FLT_MAX);

	// Ensure MinValue <= MaxValue
	if (MinValue > MaxValue)
	{
		UE_LOG(LogTireflyAttribute, Warning, TEXT("[%s] {%s} MinValue (%f) is greater than MaxValue (%f), clamping to MaxValue"),
			*FString(__FUNCTION__), *AttributeName.ToString(), MinValue, MaxValue);
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
	if (!Definition.IsValid())
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Attribute definition is not set"), *FString(__FUNCTION__));
		return;
	}

	if (!Owner)
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Owner of {%s} is not set"),
			*FString(__FUNCTION__), *AttributeName.ToString());
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
