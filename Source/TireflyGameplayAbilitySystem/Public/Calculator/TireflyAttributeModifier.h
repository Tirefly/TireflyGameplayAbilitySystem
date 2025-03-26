// Copyright Tirefly. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TireflyAttributeModifier.generated.h"


// 属性修改器实例
USTRUCT(BlueprintType)
struct FTireflyAttributeModifierInstance
{
	GENERATED_BODY()

public:
	FTireflyAttributeModifierInstance()
	{
		Handle = -1;
		ModifierType = NAME_None;
		Magnitude = 0.0f;
		Timestamp = -1;
	}

	FTireflyAttributeModifierInstance(const FTireflyAttributeModifierInstance& Another)
	{
		Handle = Another.Handle;
		ModifierType = Another.ModifierType;
		Magnitude = Another.Magnitude;
		Timestamp = Another.Timestamp;
	}

	FTireflyAttributeModifierInstance(
		int32 InHandle,
		const FName& InModifierType,
		float InMagnitude,
		const int64& InTimestamp)
	{
		Handle = InHandle;
		ModifierType = InModifierType;
		Magnitude = InMagnitude;
		Timestamp = InTimestamp;
	}

	bool operator==(const FTireflyAttributeModifierInstance& Another) const
	{
		return Handle == Another.Handle
			&& ModifierType == Another.ModifierType
			&& Magnitude == Another.Magnitude
			&& Timestamp == Another.Timestamp;
	}

	bool operator!=(const FTireflyAttributeModifierInstance& Another) const
	{
		return !(*this == Another);
	}

	FTireflyAttributeModifierInstance& operator=(const FTireflyAttributeModifierInstance& Another)
	{
		Handle = Another.Handle;
		ModifierType = Another.ModifierType;
		Magnitude = Another.Magnitude;
		Timestamp = Another.Timestamp;
		
		return *this;
	}

	friend uint32 GetTypeHash(const FTireflyAttributeModifierInstance& Instance)
	{
		uint32 Hash = HashCombine(GetTypeHash(Instance.Handle), GetTypeHash(Instance.ModifierType));
		Hash = HashCombine(Hash, GetTypeHash(Instance.Magnitude));
		Hash = HashCombine(Hash, GetTypeHash(Instance.Timestamp));
		
		return Hash;
	}

	friend FArchive& operator<<(FArchive& Ar, FTireflyAttributeModifierInstance& Modifier)
	{
		Ar << Modifier.Handle;
		Ar << Modifier.ModifierType;
		Ar << Modifier.Magnitude;
		Ar << Modifier.Timestamp;
		
		return Ar;
	}

	// 是否有效
	bool IsValid() const
	{
		return Handle != -1
			&& ModifierType != NAME_None
			&& Timestamp != -1;
	}

	void Invalid()
	{
		Handle = -1;
	}

	// 更新修改器值
	void Update(float NewMagnitude)
	{
		Magnitude = NewMagnitude;
		Timestamp = FDateTime::UtcNow().ToUnixTimestamp();
	}

	// 调试字符串
	FString DebugString() const
	{
		return FString::Printf(TEXT("Handle: %d, ModifierType: %s, Magnitude: %g, Timestamp: %lld"),
			Handle, *ModifierType.ToString(), Magnitude, Timestamp);
	}
	
public:
	// 句柄
	UPROPERTY(BlueprintReadOnly)
	int32 Handle;

	// 修改器类型
	UPROPERTY(BlueprintReadOnly)
	FName ModifierType;

	// 修改器值
	UPROPERTY(BlueprintReadOnly)
	float Magnitude;

	// 最新的更新时间戳
	UPROPERTY(BlueprintReadOnly)
	int64 Timestamp;
};