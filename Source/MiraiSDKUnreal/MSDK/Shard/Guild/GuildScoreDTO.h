#pragma once

#include "GuildScoreData.h"
#include "GuildScoreDTO.generated.h"

USTRUCT(BlueprintType)
struct FGuildScoreDTO
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, Category = "GuildScoreDTO")
	TArray<FGuildScoreData> data;
	UPROPERTY(BlueprintReadWrite, Category = "GuildScoreDTO")
	int count;
};
