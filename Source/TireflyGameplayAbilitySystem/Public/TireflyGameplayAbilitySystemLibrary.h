// Copyright Tirefly. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Attribute/TireflyAttributeInstance.h"
#include "TireflyGameplayAbilitySystemLibrary.generated.h"


class UTireflyGameplayAbilitySystemComponent;


// 技能系统函数库
UCLASS()
class TIREFLYGAMEPLAYABILITYSYSTEM_API UTireflyGameplayAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

#pragma region GameplayAbilitySystem

public:
	// 获取Actor的TireflyGameplayAbilitySystemComponent
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Ability System")
	static UTireflyGameplayAbilitySystemComponent* GetTireflyGameplayAbilitySystemComponent(const AActor* Actor);

#pragma endregion
	

#pragma region GameplayAttribute

public:
	// 获取所有GameplayAttribute的名称
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	static TArray<FName> GetAllGameplayAttributeNames();

	// 获取Actor的属性实例（基于名称）
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	static FTireflyAttributeInstance GetActorAttributeInstance(
		const AActor* Actor,
		UPARAM(Meta = (GetParamOptions = "TireflyGameplayAbilitySystemLibrary.GetAllGameplayAttributeNames"))FName AttributeName);

	// 获取Actor的属性定义（基于名称）
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	static const UTireflyAttributeDefinition* GetActorAttributeDefinition(
		const AActor* Actor,
		UPARAM(Meta = (GetParamOptions = "TireflyGameplayAbilitySystemLibrary.GetAllGameplayAttributeNames"))FName AttributeName);

	// 获取属性实例的定义
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	static const UTireflyAttributeDefinition* GetAttributeInstanceDefinition(const FTireflyAttributeInstance& Attribute);

	// 获取Actor的属性值（基于名称）
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	bool GetActorAttributeValue(
		const AActor* Actor,
		UPARAM(Meta = (GetParamOptions = "TireflyGameplayAbilitySystemLibrary.GetAllGameplayAttributeNames"))FName AttributeName,
		float& OutValue) const;
	
	// 获取Actor的属性基础值（基于名称）
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	bool GetActorAttributeBaseValue(
		const AActor* Actor,
		UPARAM(Meta = (GetParamOptions = "TireflyGameplayAbilitySystemLibrary.GetAllGameplayAttributeNames"))FName AttributeName,
		float& OutBaseValue) const;

#pragma endregion
};