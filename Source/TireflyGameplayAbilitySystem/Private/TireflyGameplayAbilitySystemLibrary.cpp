// Copyright Tirefly. All Rights Reserved.


#include "TireflyGameplayAbilitySystemLibrary.h"

#include "TireflyGameplayAbilitySystemLogChannel.h"
#include "TireflyGameplayAbilitySystemSettings.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Attribute/TireflyAttributeDefinition.h"


TArray<FName> UTireflyGameplayAbilitySystemLibrary::GetAllGameplayAttributeNames()
{
	TArray<FName> AttributeNames;
	
	const UTireflyGameplayAbilitySystemSettings* SettingsTGA = GetDefault<UTireflyGameplayAbilitySystemSettings>();
	if (!SettingsTGA)
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] SettingsTGA is nullptr"), *FString(__FUNCTION__));
		return AttributeNames;
	}

	// 加载AssetRegistry模块
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	// 创建过滤器
	FARFilter Filter;
	// 设置路径（转换为FName）
	Filter.PackagePaths.Add(FName(SettingsTGA->GameplayAttributeDefinitionDirectory.Path));
	// 设置资产类型（使用类的路径标识）
	Filter.ClassPaths.Add(UTireflyAttributeDefinition::StaticClass()->GetClassPathName());
	// 是否递归子目录
	Filter.bRecursivePaths = true;

	TArray<FAssetData> FoundAssets;
	// 强制加载扫描路径
	AssetRegistryModule.Get().ScanPathsSynchronous({ SettingsTGA->GameplayAttributeDefinitionDirectory.Path }, true);
	// 查找资产
	AssetRegistryModule.Get().GetAssets(Filter, FoundAssets);

	for (const FAssetData& AssetData : FoundAssets)
	{
		if (const UTireflyAttributeDefinition* AttributeDefinition = Cast<UTireflyAttributeDefinition>(AssetData.GetAsset()))
		{
			AttributeNames.Add(AttributeDefinition->GetGameplayAttributeNameDefine());
		}
	}
	
	return AttributeNames;
}
