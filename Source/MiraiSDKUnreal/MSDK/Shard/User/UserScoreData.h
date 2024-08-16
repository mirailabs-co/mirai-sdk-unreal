#pragma once

#include "ShardsTechUser.h"
#include "UserScoreData.generated.h"

USTRUCT(BlueprintType)
struct FUserScoreData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "UserScoreData")
	FString _id;
	UPROPERTY(BlueprintReadWrite, Category = "UserScoreData")
	FShardsTechUser user;
	UPROPERTY(BlueprintReadWrite, Category = "UserScoreData")
	int score;
};
