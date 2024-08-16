#pragma once

#include "MiraiSDKUnreal/MSDK/Shard/User/ShardsTechUser.h"
#include "ChatMessageData.generated.h"

USTRUCT()
struct FChatMessageData
{
	GENERATED_BODY()

	UPROPERTY()
	FString _id;

	UPROPERTY()
	FString clientId;

	UPROPERTY()
	FString guild;

	UPROPERTY()
	FShardsTechUser user;

	UPROPERTY()
	FString message;

	UPROPERTY()
	FDateTime createdAt;
};
