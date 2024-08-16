#pragma once

#include "FractionsPriceData.generated.h"

USTRUCT()
struct FFractionsPriceData
{
	GENERATED_BODY()

	UPROPERTY()
	float index;
	UPROPERTY()
	double price;
};
