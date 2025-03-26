// Copyright Tirefly. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Calculator/TireflyAttributeEvaluator.h"
#include "Engine/DeveloperSettings.h"
#include "TireflyGameplayAbilitySystemSettings.generated.h"


// 技能系统设置
UCLASS(DefaultConfig, Config = TireflyGameplayAbilitySystemSettings)
class TIREFLYGAMEPLAYABILITYSYSTEM_API UTireflyGameplayAbilitySystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

#pragma region DeveloperSettings

public:
	/** Gets the settings container name for the settings, either Project or Editor */
	virtual FName GetContainerName() const override { return FName("Project"); }

	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override { return FName("Game"); }

	/** The unique name for your section of settings, uses the class's FName. */
	virtual FName GetSectionName() const override { return FName("Tirefly Gameplay Ability System"); }

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

protected:
	/** Gets the section text, uses the classes DisplayName by default. */
	virtual FText GetSectionText() const override { return FText::FromString("Tirefly Gameplay Ability System Settings"); }

	/** Gets the description for the section, uses the classes ToolTip by default. */
	virtual FText GetSectionDescription() const override { return FText::FromString("Developer settings of Tirefly Gameplay Ability System"); }
	
#endif

#pragma endregion


#pragma region GameplayAttributeSettings

public:
	UPROPERTY(Config, EditAnywhere, Category = "Tirefly Gameplay Attribute", Meta = (
		DisplayName = "属性定义路径", RelativeToGameContentDir, LongPackageName))
	FDirectoryPath GameplayAttributeDefinitionDirectory;

	UPROPERTY(Config, EditAnywhere, Category = "Tirefly Gameplay Attribute", Meta = (
		DisplayName = "通用属性求值器"))
	TSoftObjectPtr<UTireflyAttributeEvaluator> GenericAttributeEvaluator;

#pragma endregion
};
