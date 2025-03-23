// Copyright Tirefly. All Rights Reserved.


#include "Calculator/TireflyAttributeGenericEvaluator.h"


UTireflyAttributeGenericEvaluator::UTireflyAttributeGenericEvaluator(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ModifiersDefine = {
		TireflyGenericAttrModType::ModType_Add,
		TireflyGenericAttrModType::ModType_Subtract,
		TireflyGenericAttrModType::ModType_MultiplyAdditive,
		TireflyGenericAttrModType::ModType_MultiplySubtractive,
		TireflyGenericAttrModType::ModType_MultiplyCompound,
		TireflyGenericAttrModType::ModType_Divide,
		TireflyGenericAttrModType::ModType_Override
	};
}