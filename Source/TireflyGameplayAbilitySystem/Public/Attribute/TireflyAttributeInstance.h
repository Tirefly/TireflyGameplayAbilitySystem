// Copyright Tirefly. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TireflyAttributeInstance.generated.h"


class UTireflyAttributeDefinition;


// 属性实例，游戏运行时使用的数据结构
USTRUCT(BlueprintType)
struct FTireflyAttributeInstance
{
	GENERATED_BODY()

public:
	float BaseValue;

	UPROPERTY()
	TObjectPtr<UTireflyAttributeDefinition> Definition;
};
