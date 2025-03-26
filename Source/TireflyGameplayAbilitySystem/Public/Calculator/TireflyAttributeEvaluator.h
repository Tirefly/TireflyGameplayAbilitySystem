// Copyright Tirefly. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TireflyAttributeModifier.h"
#include "TireflyAttributeEvaluator.generated.h"


// 属性求值器
UCLASS(Blueprintable, BlueprintType)
class TIREFLYGAMEPLAYABILITYSYSTEM_API UTireflyAttributeEvaluator : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
#pragma region PrimaryDataAsset

public:
	UTireflyAttributeEvaluator(const FObjectInitializer& ObjectInitializer);
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

public:
	// 属性求值器类型
	static const FPrimaryAssetType TireflyAttributeEvaluator;

#pragma endregion
	

#pragma region AttributeCalculation

public:
	// 计算属性当前值
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Evaluator")
	float EvaluateCurrentValue(float BaseValue,
		const TMap<int32, FTireflyAttributeModifierInstance>& Modifiers) const;
	virtual float EvaluateCurrentValue_Implementation(float BaseValue,
		const TMap<int32, FTireflyAttributeModifierInstance>& Modifiers) const { return 0.f; }

public:
	// 属性求值器类型
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Evaluator", Meta = (DisplayName = "求值器类型"))
	FName EvaluatorType;

	// 该属性求值器的所有修改器定义
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Evaluator", Meta = (DisplayName = "修改器定义"))
	TArray<FName> ModifiersDefine;

#pragma endregion
};
