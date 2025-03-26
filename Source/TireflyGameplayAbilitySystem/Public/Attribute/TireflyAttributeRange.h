// Copyright Tirefly. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TireflyAttributeRange.generated.h"


// 属性范围
USTRUCT(BlueprintType)
struct FTireflyAttributeRange
{
	GENERATED_BODY()

#pragma region MinValue
	
public:
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "属性是否有最小值"))
	bool bHasMinValue = false;
	
	// 属性最小值是否使用其他属性
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "属性最小值设置（是否使用其他属性）",
		EditCondition = "bHasMinValue", EditConditionHides))
	bool bMinValueUseAttribute = false;

	// 属性最小值
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "属性最小值",
		EditCondition = "bHasMinValue && !bMinValueUseAttribute", EditConditionHides))
	float MinValue = 0.f;

	// 属性最小值使用的属性类型
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "属性最小值属性",
		EditCondition = "bHasMinValue && bMinValueUseAttribute", EditConditionHides,
		GetOptions = "GetGameplayAttributeNamesExceptThis"))
	FName MinValueAttribute = NAME_None;

#pragma endregion


#pragma region MaxValue

public:
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "属性是否有最大值"))
	bool bHasMaxValue = false;

	// 属性最大值是否使用其他属性
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "属性最大值设置（是否使用其他属性）",
		EditCondition = "bHasMaxValue", EditConditionHides))
	bool bMaxValueUseAttribute = false;

	// 属性最大值
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "属性最大值",
		EditCondition = "bHasMaxValue && !bMaxValueUseAttribute", EditConditionHides))
	float MaxValue = 0.f;

	// 属性最大值使用的属性类型
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "属性最大值属性",
		EditCondition = "bHasMaxValue && bMaxValueUseAttribute", EditConditionHides,
		GetOptions = "GetGameplayAttributeNamesExceptThis"))
	FName MaxValueAttribute = NAME_None;

#pragma endregion
};
