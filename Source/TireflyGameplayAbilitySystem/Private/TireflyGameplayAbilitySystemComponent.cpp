// Copyright Tirefly. All Rights Reserved.


#include "TireflyGameplayAbilitySystemComponent.h"

#include "TireflyGameplayAbilitySystemLogChannel.h"
#include "Net/UnrealNetwork.h"


UTireflyGameplayAbilitySystemComponent::UTireflyGameplayAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTireflyGameplayAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTireflyGameplayAbilitySystemComponent::GetLifetimeReplicatedProps(
	TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION(UTireflyGameplayAbilitySystemComponent, AttributeInstances, COND_OwnerOnly);
}

void UTireflyGameplayAbilitySystemComponent::AddAttribute(
	UTireflyAttributeDefinition* Definition,
	float BaseValue)
{
	if (!Definition)
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Definition is nullptr"), *FString(__FUNCTION__));
		return;
	}

	AttributeInstances.Add(FTireflyAttributeInstance(Definition, this, BaseValue));
}

void UTireflyGameplayAbilitySystemComponent::RemoveAttribute(UTireflyAttributeDefinition* Definition)
{
	if (!Definition)
	{
		UE_LOG(LogTireflyAttribute, Error, TEXT("[%s] Definition is nullptr"), *FString(__FUNCTION__));
		return;
	}

	int32 IndexToRemove = -1;
	for (int32 i = 0; i < AttributeInstances.Num(); ++i)
	{
		if (AttributeInstances[i].GetDefinition() == Definition)
		{
			IndexToRemove = i;
			break;
		}
	}

	if (IndexToRemove != -1)
	{
		AttributeInstances.RemoveAt(IndexToRemove);
	}
}

bool UTireflyGameplayAbilitySystemComponent::GetAttributeValue(FName AttributeName, float& OutValue) const
{
	for (const auto& AttributeInstance : AttributeInstances)
	{
		if (AttributeInstance.GetAttributeName() == AttributeName)
		{
			OutValue = AttributeInstance.GetCurrentValue();
			return true;
		}
	}

	return false;
}

bool UTireflyGameplayAbilitySystemComponent::GetAttributeBaseValue(FName AttributeName, float& OutBaseValue) const
{
	for (const auto& AttributeInstance : AttributeInstances)
	{
		if (AttributeInstance.GetAttributeName() == AttributeName)
		{
			OutBaseValue = AttributeInstance.GetBaseValue();
			return true;
		}
	}

	return false;
}
