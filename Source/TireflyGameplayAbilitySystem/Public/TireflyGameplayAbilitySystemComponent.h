// Copyright Tirefly. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Attribute/TireflyAttributeInstance.h"
#include "TireflyGameplayAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Tirefly), meta=(BlueprintSpawnableComponent))
class TIREFLYGAMEPLAYABILITYSYSTEM_API UTireflyGameplayAbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region ActorComponent

public:
	// Sets default values for this component's properties
	UTireflyGameplayAbilitySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
#pragma endregion


#pragma region GameplayAttribute

public:
	// 为Actor添加属性
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Tirefly Gameplay Attribute")
	void AddAttribute(UTireflyAttributeDefinition* Definition, float BaseValue);

	// 移除Actor的属性
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Tirefly Gameplay Attribute")
	void RemoveAttribute(UTireflyAttributeDefinition* Definition);

	// 获取属性实例（基于名称）
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	FTireflyAttributeInstance GetAttributeInstance(
		UPARAM(Meta = (GetParamOptions = "TireflyGameplayAbilitySystemLibrary.GetAllGameplayAttributeNames"))FName AttributeName);

	// 获取属性定义（基于名称）
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	const UTireflyAttributeDefinition* GetAttributeDefinition(
		UPARAM(Meta = (GetParamOptions = "TireflyGameplayAbilitySystemLibrary.GetAllGameplayAttributeNames"))FName AttributeName);

	// 获取属性值（基于名称）
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	bool GetAttributeValue(
		UPARAM(Meta = (GetParamOptions = "TireflyGameplayAbilitySystemLibrary.GetAllGameplayAttributeNames"))FName AttributeName,
		float& OutValue) const;
	
	// 获取属性基础值（基于名称）
	UFUNCTION(BlueprintCallable, Category = "Tirefly Gameplay Attribute")
	bool GetAttributeBaseValue(
		UPARAM(Meta = (GetParamOptions = "TireflyGameplayAbilitySystemLibrary.GetAllGameplayAttributeNames"))FName AttributeName,
		float& OutBaseValue) const;

	// 处理属性值改变
	UFUNCTION()
	void HandleAttributeValueChanged(const FTireflyAttributeInstance& Attribute) {}

	// 处理属性基础值改变
	UFUNCTION()
	void HandleAttributeBaseValueChanged(const FTireflyAttributeInstance& Attribute) {}

protected:
	// 属性实例集合
	UPROPERTY(Replicated)
	TArray<FTireflyAttributeInstance> AttributeInstances;

#pragma endregion
};
