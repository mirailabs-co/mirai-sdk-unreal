#pragma once
#include "UserScoreData.h"

#include "UserScoresDTO.generated.h"

USTRUCT(BlueprintType)
struct FUserScoresDTO
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "FUserScoresDTO")
	TArray<FUserScoreData> data;
	UPROPERTY(BlueprintReadWrite, Category = "FUserScoresDTO")
	int count;
};
