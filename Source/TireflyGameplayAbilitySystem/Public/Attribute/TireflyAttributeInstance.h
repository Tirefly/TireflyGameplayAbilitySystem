// Copyright Tirefly. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Calculator/TireflyAttributeModifier.h"
#include "TireflyAttributeInstance.generated.h"


class UTireflyGameplayAbilitySystemComponent;
class UTireflyAttributeDefinition;


// 属性实例，游戏运行时使用的数据结构
USTRUCT(BlueprintType)
struct FTireflyAttributeInstance
{
	GENERATED_BODY()

#pragma region Constuctor
	
public:
	FTireflyAttributeInstance()
	{
		BaseValue = 0.0f;
		CurrentValue = 0.0f;
	}

	FTireflyAttributeInstance(
		UTireflyAttributeDefinition* Def,
		UTireflyGameplayAbilitySystemComponent* InOwner,
		float InBaseValue)
	{
		Definition = Def;
		Owner = InOwner;
		
		SetBaseValue(InBaseValue);
	}

	FTireflyAttributeInstance(const FTireflyAttributeInstance& Another)
	{
		Definition = Another.Definition;
		Owner = Another.Owner;
		Modifiers = Another.Modifiers;
		
		SetBaseValue(Another.BaseValue);
	}

	FTireflyAttributeInstance& operator=(const FTireflyAttributeInstance& Another)
	{
		Definition = Another.Definition;
		Owner = Another.Owner;
		Modifiers = Another.Modifiers;

		SetBaseValue(Another.BaseValue);

		return *this;
	}

#pragma endregion


#pragma region Serialization

public:
	friend FArchive& operator<<(FArchive& Ar, FTireflyAttributeInstance& Instance)
	{
		Ar << Instance.Definition;
		Ar << Instance.Modifiers;
		Ar << Instance.BaseValue;
		Ar << Instance.CurrentValue;

		return Ar;
	}

#pragma endregion


#pragma region Getter

public:
	// 是否有效
	bool IsValid() const;

	// 获取属性名称
	FName GetAttributeName() const;

	// 调试字符串
	FString DebugString() const;

	// 获取用于UI展示的字符串
	FText GetShowcaseForUI() const;

	// 获取属性定义
	const UTireflyAttributeDefinition* GetDefinition() const { return Definition; }

	// 获取基础值
	float GetBaseValue() const { return BaseValue; }

	// 获取当前值
	float GetCurrentValue() const { return CurrentValue; }
	
#pragma endregion


#pragma region Setter

protected:
	float ClampAttributeValue(float InValue) const;

public:
	// 添加修改器
	void AddModifier(const FTireflyAttributeModifierInstance& Modifier);

	// 移除修改器
	void RemoveModifier(const FTireflyAttributeModifierInstance& Modifier);
	// 移除修改器
	void RemoveModifier(int32 ModifierHandle);
	
	// 设置基础值
	void SetBaseValue(float NewBaseValue);
	
	// 更新属性当前值
	void UpdateCurrentValue();

#pragma endregion


#pragma region Data
	
protected:
	// 属性定义
	UPROPERTY()
	TObjectPtr<UTireflyAttributeDefinition> Definition;

	// 属性所属者
	UPROPERTY()
	TObjectPtr<UTireflyGameplayAbilitySystemComponent> Owner;

	// 修改器集合
	UPROPERTY()
	TMap<int32, FTireflyAttributeModifierInstance> Modifiers;

	// 基础值
    UPROPERTY()
    float BaseValue;

	// 当前值
	UPROPERTY()
	float CurrentValue;

#pragma endregion
};
