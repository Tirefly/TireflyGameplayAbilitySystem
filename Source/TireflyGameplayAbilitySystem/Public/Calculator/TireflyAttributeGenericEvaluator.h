// Copyright Tirefly. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TireflyAttributeEvaluator.h"
#include "TireflyAttributeGenericEvaluator.generated.h"


// 预设的通用属性求值器的修改器类型定义
namespace TireflyGenericAttrModType
{
	static FName ModType_Add = FName("Add");
	static FName ModType_Subtract = FName("Subtract");
	static FName ModType_MultiplyAdditive = FName("Multiply (Additive)");
	static FName ModType_MultiplySubtractive = FName("Multiply (Subtractive)");
	static FName ModType_MultiplyCompound = FName("Multiply (Compound)");
	static FName ModType_Divide = FName("Divide");
	static FName ModType_Override = FName("Override");
}


// 预设的通用属性求值器
UCLASS()
class TIREFLYGAMEPLAYABILITYSYSTEM_API UTireflyAttributeGenericEvaluator : public UTireflyAttributeEvaluator
{
	GENERATED_BODY()

public:
	UTireflyAttributeGenericEvaluator(const FObjectInitializer& ObjectInitializer);
};
