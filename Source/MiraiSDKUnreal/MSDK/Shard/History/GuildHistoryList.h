#pragma once

#include "GuildHistory.h"
#include "GuildHistoryList.generated.h"

USTRUCT(BlueprintType)
struct FGuildHistoryList
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FGuildHistory> data;
	UPROPERTY()
	int count;
};
