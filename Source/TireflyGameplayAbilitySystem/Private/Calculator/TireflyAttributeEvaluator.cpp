// Copyright Tirefly. All Rights Reserved.


#include "Calculator/TireflyAttributeEvaluator.h"


const FPrimaryAssetType UTireflyAttributeEvaluator::TireflyAttributeEvaluator = TEXT("Tirefly Attribute Evaluator");


UTireflyAttributeEvaluator::UTireflyAttributeEvaluator(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FPrimaryAssetId UTireflyAttributeEvaluator::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(TireflyAttributeEvaluator, EvaluatorType);
}
