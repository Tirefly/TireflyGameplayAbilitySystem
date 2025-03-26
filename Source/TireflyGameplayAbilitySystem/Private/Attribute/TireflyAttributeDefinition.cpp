// Copyright Tirefly. All Rights Reserved.


#include "Attribute/TireflyAttributeDefinition.h"

#include "TireflyGameplayAbilitySystemLibrary.h"
#include "TireflyGameplayAbilitySystemSettings.h"


const FPrimaryAssetType UTireflyAttributeDefinition::TireflyAttributeDefinition = TEXT("Tirefly Attribute Definition");


UTireflyAttributeDefinition::UTireflyAttributeDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (const UTireflyGameplayAbilitySystemSettings* Settings = GetDefault<UTireflyGameplayAbilitySystemSettings>())
	{
		AttributeEvaluator = Settings->GenericAttributeEvaluator.LoadSynchronous();
	}
}

FPrimaryAssetId UTireflyAttributeDefinition::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(TireflyAttributeDefinition, AttributeNameDefine);
}

TArray<FName> UTireflyAttributeDefinition::GetGameplayAttributeNamesExceptThis() const
{
	TArray<FName> AttributeNames = UTireflyGameplayAbilitySystemLibrary::GetAllGameplayAttributeNames();
	AttributeNames.Remove(AttributeNameDefine);
	
	return AttributeNames;
}

UTireflyAttributeEvaluator* UTireflyAttributeDefinition::GetAttributeEvaluator() const
{
	return AttributeEvaluator;
}
