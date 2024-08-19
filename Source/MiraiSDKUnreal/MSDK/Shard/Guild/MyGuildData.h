#pragma once
#include "GuildData.h"
#include "MyGuildData.generated.h"

USTRUCT(BlueprintType)
struct FMyGuildData : public FGuildData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "MyGuildData")
	TArray<FShardsTechUser> Users;

	UPROPERTY(BlueprintReadWrite, Category = "MyGuildData")
	int64 EndAllowUpdateTimestamp;

	UPROPERTY(BlueprintReadWrite, Category = "MyGuildData")
	int64 StartAllowUpdateTimestamp;
};