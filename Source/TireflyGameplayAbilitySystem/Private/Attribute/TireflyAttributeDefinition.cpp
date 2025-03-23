// Copyright Tirefly. All Rights Reserved.


#include "Attribute/TireflyAttributeDefinition.h"

#include "TireflyGameplayAbilitySystemLibrary.h"


const FPrimaryAssetType UTireflyAttributeDefinition::TireflyAttributeDefinition = TEXT("Tirefly Attribute Definition");


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
