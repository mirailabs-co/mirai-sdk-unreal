#pragma once

#include "BaseHistory.h"
#include "MiraiSDKUnreal/MSDK/Shard/User/ShardsTechUser.h"
#include "GuildHistory.generated.h"

USTRUCT(BlueprintType)
struct FGuildHistory : public FBaseHistory
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "History")
	FString Guild;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "History")
	FShardsTechUser User;
};