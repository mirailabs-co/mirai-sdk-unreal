#pragma once

#include "CoreMinimal.h"
#include "Serialization/JsonSerializer.h"
#include "ShardsTechConfig.generated.h"

USTRUCT(BlueprintType)
struct FShardsTechConfig
{
	GENERATED_BODY()
	
public:	
	FString ClientId;
	FString LinkDapp;
	double Fee;
	int32 RewardShareForMembers;
	int32 TxGuildOwnerShare;
	int32 GuildOwnerShare;
	int32 Deadline;
	bool SupportWebBrowser;

	FShardsTechConfig() {}

	FShardsTechConfig(const FString& clientId, const FString& linkDapp, double fee, int32 rewardShareForMembers, int32 txGuildOwnerShare, int32 guildOwnerShare, int32 deadline, bool supportWebBrowser)
		: ClientId(clientId)
		, LinkDapp(linkDapp)
		, Fee(fee)
		, RewardShareForMembers(rewardShareForMembers)
		, TxGuildOwnerShare(txGuildOwnerShare)
		, GuildOwnerShare(guildOwnerShare)
		, Deadline(deadline)
		, SupportWebBrowser(supportWebBrowser)
	{}

	void Serialize(FArchive& ar)
	{
		ar << ClientId;
		ar << LinkDapp;
		ar << Fee;
		ar << RewardShareForMembers;
		ar << TxGuildOwnerShare;
		ar << GuildOwnerShare;
		ar << Deadline;
		ar << SupportWebBrowser;
	}
};