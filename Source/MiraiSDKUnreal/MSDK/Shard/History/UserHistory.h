#pragma once

#include "BaseHistory.h"
#include "MiraiSDKUnreal/MSDK/Shard/Guild/GuildData.h"
#include "UserHistory.generated.h"

USTRUCT(BlueprintType)
struct FUserHistory : public FBaseHistory
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "History")
	FString User;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "History")
	FGuildData Guild;
};