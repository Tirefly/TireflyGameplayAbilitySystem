// Copyright Tirefly. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TireflyGameplayAbilitySystemLibrary.generated.h"


// 技能系统函数库
UCLASS()
class TIREFLYGAMEPLAYABILITYSYSTEM_API UTireflyGameplayAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

#pragma region GameplayAttribute

public:
	// 获取所有GameplayAttribute的名称
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	static TArray<FName> GetAllGameplayAttributeNames();

#pragma endregion
};
