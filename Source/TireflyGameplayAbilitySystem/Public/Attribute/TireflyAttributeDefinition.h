// Copyright Tirefly. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TireflyAttributeDefinition.generated.h"


class UTireflyAttributeEvaluator;


// 属性范围
USTRUCT(BlueprintType)
struct FTireflyAttributeRange
{
	GENERATED_BODY()

public:
	// 属性最小值是否使用其他属性
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "属性最小值设置（是否使用其他属性）"))
	bool bMinValueUseAttribute = false;

	// 属性最小值
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "属性最小值",
		EditCondition = "!bMinValueUseAttribute", EditConditionHides))
	float MinValue;

	// 属性最小值使用的属性类型
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "属性最小值属性",
		EditCondition = "bMinValueUseAttribute", EditConditionHides,
		GetOptions = "GetGameplayAttributeNamesExceptThis"))
	FName MinValueAttribute;

	// 属性最大值是否使用其他属性
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "属性最大值设置（是否使用其他属性）"))
	bool bMaxValueUseAttribute = false;

	// 属性最大值
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "属性最大值",
		EditCondition = "!bMaxValueUseAttribute", EditConditionHides))
	float MaxValue;

	// 属性最大值使用的属性类型
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "属性最大值属性",
		EditCondition = "bMaxValueUseAttribute", EditConditionHides,
		GetOptions = "GetGameplayAttributeNamesExceptThis"))
	FName MaxValueAttribute;
	
};


// 属性定义
UCLASS(Blueprintable, BlueprintType)
class TIREFLYGAMEPLAYABILITYSYSTEM_API UTireflyAttributeDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

#pragma region PrimaryDataAsset

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

public:
	// 属性定义资产类型
	static const FPrimaryAssetType TireflyAttributeDefinition;

#pragma endregion


#pragma region AttributeHelper

public:
	// 帮助函数：获取除当前属性外的所有属性名称
	UFUNCTION()
	TArray<FName> GetGameplayAttributeNamesExceptThis() const;

#pragma endregion


#pragma region AttributeDefinition

public:
	// 获取属性名定义
	UFUNCTION()
	FName GetGameplayAttributeNameDefine() const { return AttributeNameDefine; }

	// 获取属性求值器
	UFUNCTION()
	UTireflyAttributeEvaluator* GetAttributeEvaluator() const;

	// 获取属性名称
	UFUNCTION()
	FText GetGameplayAttributeName() const { return AttributeDescription; }

	// 获取属性描述
	UFUNCTION()
	FText GetGameplayAttributeDescription() const { return AttributeDescription; }

	// 获取是否在UI中显示
	UFUNCTION()
	bool IsShowInUI() const { return bShowInUI; }

	// 获取是否以百分比显示
	UFUNCTION()
	bool IsAsPercentage() const { return bAsPercentage; }

protected:
	// 属性名定义
	UPROPERTY(EditAnywhere, Category = "Meta", Meta = (DisplayName = "属性名定义"))
	FName AttributeNameDefine;

	// 属性范围
	UPROPERTY(EditAnywhere, Category = "Meta", Meta = (DisplayName = "属性范围"))
	FTireflyAttributeRange AttributeRange;

	// 属性求值器
	UPROPERTY(EditAnywhere, Category = "Meta", Meta = (DisplayName = "属性计算器"))
	TObjectPtr<UTireflyAttributeEvaluator> AttributeEvaluator;

	// 属性名称
	UPROPERTY(EditAnywhere, Category = "Text", Meta = (DisplayName = "属性名称（文本）"))
	FText AttributeName;

	// 属性描述
	UPROPERTY(EditAnywhere, Category = "Text", Meta = (DisplayName = "属性描述（文本）"))
	FText AttributeDescription;

	// 是否在UI中显示
	UPROPERTY(EditAnywhere, Category="UI", Meta = (DisplayName = "是否在UI中显示"))
	bool bShowInUI = true;

	// 是否以百分比显示
	UPROPERTY(EditAnywhere, Category="UI", Meta = (DisplayName = "是否以百分比显示"))
	bool bAsPercentage = false;

#pragma endregion
};
