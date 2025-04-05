// Copyright Tirefly. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TireflyAttributeRange.h"
#include "Engine/DataAsset.h"
#include "TireflyAttributeDefinition.generated.h"


class UTireflyAttributeEvaluator;


// 属性定义
UCLASS(Blueprintable, BlueprintType)
class TIREFLYGAMEPLAYABILITYSYSTEM_API UTireflyAttributeDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

#pragma region PrimaryDataAsset

public:
	UTireflyAttributeDefinition(const FObjectInitializer& ObjectInitializer);
	
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
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	FName GetGameplayAttributeNameDefine() const { return AttributeNameDefine; }

	// 获取属性范围
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	const FTireflyAttributeRange& GetAttributeRange() const { return AttributeRange; }

	// 获取属性求值器
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	UTireflyAttributeEvaluator* GetAttributeEvaluator() const;

	// 获取属性名称
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	FText GetGameplayAttributeName() const { return AttributeDescription; }

	// 获取属性描述
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	FText GetGameplayAttributeDescription() const { return AttributeDescription; }

	// 获取是否在UI中显示
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	bool IsShowInUI() const { return bShowInUI; }

	// 获取是否作为小数显示
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	bool IsAsDecimal() const { return bAsDecimal; }

	// 获取是否以百分比显示
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
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

	// 属性名称（推荐使用 StringTable）
	UPROPERTY(EditAnywhere, Category = "Text", Meta = (DisplayName = "属性名称（文本）"))
	FText AttributeName;

	// 属性描述
	UPROPERTY(EditAnywhere, Category = "Text", Meta = (DisplayName = "属性描述（文本）"))
	FText AttributeDescription;

	// 是否在UI中显示
	UPROPERTY(EditAnywhere, Category="UI", Meta = (DisplayName = "是否在UI中显示"))
	bool bShowInUI = true;

	// 是否作为小数显示
	UPROPERTY(EditAnywhere, Category="UI", Meta = (DisplayName = "是否作为小数显示", EditCondition = "bShowInUI", EditConditionHides))
	bool bAsDecimal = true;

	// 是否作为百分数显示
	UPROPERTY(EditAnywhere, Category="UI", Meta = (DisplayName = "是否作为百分数显示", EditCondition = "bShowInUI", EditConditionHides))
	bool bAsPercentage = false;

#pragma endregion
};
