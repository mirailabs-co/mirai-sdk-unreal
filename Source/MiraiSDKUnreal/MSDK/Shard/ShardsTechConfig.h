#pragma once

#include "CoreMinimal.h"
#include "Serialization/JsonSerializer.h"
#include "ShardsTechConfig.generated.h"

USTRUCT(BlueprintType)
struct FShardsTechConfig
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FString clientId;
	UPROPERTY()
	FString linkDapp;
	UPROPERTY()
	double fee;
	UPROPERTY()
	int32 rewardShareForMembers;
	UPROPERTY()
	int32 txGuildOwnerShare;
	UPROPERTY()
	int32 guildOwnerShare;
	UPROPERTY()
	int32 deadline;
	UPROPERTY()
	bool supportWebBrowser;
};