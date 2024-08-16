#pragma once

#include "GuildData.h"
#include "GuildScoreData.generated.h"

USTRUCT(BlueprintType)
struct FGuildScoreData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "GuildScoreData")
	FString _id;
	UPROPERTY(BlueprintReadWrite, Category = "GuildScoreData")
	FGuildData guild;
	UPROPERTY(BlueprintReadWrite, Category = "GuildScoreData")
	int score;
};
