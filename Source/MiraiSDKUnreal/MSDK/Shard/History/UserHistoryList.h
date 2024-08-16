#pragma once

#include "UserHistory.h"
#include "UserHistoryList.generated.h"

USTRUCT(BlueprintType)
struct FUserHistoryList
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FUserHistory> data;
	UPROPERTY()
	int count;
};
