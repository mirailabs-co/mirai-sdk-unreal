#pragma once
#include "CoreMinimal.h"
#include "ProfitPercentConfig.h"
#include "MiraiSDKUnreal/MSDK/Shard/User/ShardsTechUser.h"
#include "GuildData.generated.h"

USTRUCT(BlueprintType)
struct FGuildData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString _id;

	UPROPERTY()
	FString address;

	UPROPERTY()
	FShardsTechUser owner;

	UPROPERTY()
	FString clientId;

	UPROPERTY()
	FString name;

	// UPROPERTY()
	// FString metadata;

	UPROPERTY()
	double seatPrice;

	UPROPERTY()
	float rewardShareForMembers;

	UPROPERTY()
	float txGuildOwnerShare;

	UPROPERTY()
	float guildOwnerShare;

	UPROPERTY()
	int maxMembers;

	UPROPERTY()
	int numberAllowUpdate;

	UPROPERTY()
	FString chain;

	UPROPERTY()
	bool isDeleted;

	UPROPERTY()
	int userCount;

	UPROPERTY()
	FDateTime createdAt;

	UPROPERTY()
	FProfitPercentConfig _profitPercentConfig;
};