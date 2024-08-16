#include "ShardsTech.h"

#include "Guild/GuildScoreDTO.h"
#include "History/GuildHistoryList.h"
#include "History/UserHistory.h"
#include "History/UserHistoryList.h"
#include "MiraiSDKUnreal/MSDK/GameUtils.h"
#include "Serialization/JsonSerializable.h"

#include "MiraiSDKUnreal/MSDK/RestApi.h"

FShardsTechUser ShardsTech::MyUser;
FMyGuildData ShardsTech::MyGuild;
FShardsTechConfig ShardsTech::GameConfig;
TArray<FLeaderboardData> ShardsTech::ListLeaderboards;
TArray<FJoinGuildRequest> ShardsTech::ListJoinGuildRequests;

void ShardsTech::Init(EShardEnviron env)
{
	switch (env)
	{
		case EShardEnviron::Dev:
			ShardAPI = FString("https://api-dev.shards.tech/v1/");
			break;
		case EShardEnviron::Prod:
			break;
	}
	auto CallbackSuccess = [](auto responeseData)
	{
		GameConfig = responeseData;
		UE_LOG(LogTemp, Log, TEXT("Id: %s"), *MyUser.Id);
		UE_LOG(LogTemp, Log, TEXT("ClientId: %s"), *MyUser.ClientId);
		UE_LOG(LogTemp, Log, TEXT("UserId: %s"), *MyUser.UserId);
		UE_LOG(LogTemp, Log, TEXT("Address: %s"), *MyUser.Address);
	};
	RestApi::Request<FShardsTechConfig>(ShardAPI + "game-config", "GET", "", CallbackSuccess);
}
void ShardsTech::Login()
{
	UE_LOG(LogTemp, Log, TEXT("Start login"));
}
void ShardsTech::Logout()
{
}

void ShardsTech::FetchMyUser(TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		MyUser = responeseData;
		UE_LOG(LogTemp, Log, TEXT("Id: %s"), *MyUser.Id);
		UE_LOG(LogTemp, Log, TEXT("ClientId: %s"), *MyUser.ClientId);
		UE_LOG(LogTemp, Log, TEXT("UserId: %s"), *MyUser.UserId);
		UE_LOG(LogTemp, Log, TEXT("Address: %s"), *MyUser.Address);
		if (onSuccess != nullptr)
			onSuccess();
	};
	RestApi::Request<FShardsTechUser>(ShardAPI + "users", "GET", "", CallbackSuccess, onFailed);
}

void ShardsTech::FetchMyGuild(TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		MyGuild = responeseData;
		UE_LOG(LogTemp, Log, TEXT("Id: %s"), *MyGuild._id);
		UE_LOG(LogTemp, Log, TEXT("Owner id: %s"), *MyGuild.owner.UserId);
		UE_LOG(LogTemp, Log, TEXT("Member count: %d"), MyGuild.Users.Num());
		UE_LOG(LogTemp, Log, TEXT("Member max: %d"), MyGuild.maxMembers);
		if (onSuccess != nullptr)
			onSuccess();
	};
	RestApi::Request<FMyGuildData>(ShardAPI + "guilds/guild-of-user", "GET", "", CallbackSuccess, onFailed);
}
void ShardsTech::FetchMySeatOnSale(TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		if (onSuccess != nullptr)
			onSuccess();
	};
	RestApi::Request<FSellSeatData>(ShardAPI + "user-sell-guild/my", "GET", "", CallbackSuccess, onFailed);
}

void ShardsTech::GetLeaderboards(TFunction<void(TArray<FLeaderboardData>)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		ListLeaderboards = responeseData;
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	RestApi::Request<TArray<FLeaderboardData>>(ShardAPI + "leader-boards", "GET", "", CallbackSuccess, onFailed);
}


void ShardsTech::GetGuildScores(FString leaderBoardId, FString name, int page, int limit, ESortType sort,
	TFunction<void(FGuildScoreDTO)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	
	FString url = FString::Printf(TEXT("guild-score?leaderBoardId=%s"), *leaderBoardId);
	if (!name.IsEmpty())
	{
		url.Append(FString::Printf(TEXT("&name=%s"), *name));
	}
	url.Append(FString::Printf(TEXT("&page=%d&limit=%d&sort=%s"), page, limit, *GameUtils::EnumToString(sort)));


	RestApi::Request<FGuildScoreDTO>(ShardAPI + url, "GET", "", CallbackSuccess);
}

void ShardsTech::CreateJoinGuildRequest(FString guildId, TFunction<void(FJoinGuildRequest)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess, onFailed](auto request)
	{
		ShardsTech::GetJoinGuildRequestsOfUser([onSuccess, onFailed, request](auto lstRequest)
		{
			if (onSuccess != nullptr)
				onSuccess(request);
		}, onFailed);
	};
	RestApi::Request<FJoinGuildRequest>(ShardAPI + "join-guild-request/" + guildId, "POST", "", CallbackSuccess, onFailed);
}

void ShardsTech::GetJoinGuildRequestsOfUser(TFunction<void(TArray<FJoinGuildRequest>)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		ListJoinGuildRequests = responeseData;
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	RestApi::Request<TArray<FJoinGuildRequest>>(ShardAPI + "join-guild-request", "GET", "", CallbackSuccess, onFailed);
}

void ShardsTech::GetJoinGuildRequestsOfGuild(FString guildId, TFunction<void(TArray<FJoinGuildRequest>)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	RestApi::Request<TArray<FJoinGuildRequest>>(ShardAPI + "join-guild-request/" + guildId, "GET", "", CallbackSuccess, onFailed);
}

void ShardsTech::AcceptJoinGuildRequest(FString guildId, FString userId, TFunction<void(FJoinGuildRequest)> onSuccess, TFunction<void()> onFailed)
{
	FAcceptJoinGuildRequestData requestData
	{
		guildId, userId
	};
	FString jsonData;
	FJsonObjectConverter::UStructToJsonObjectString(requestData, jsonData);

	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	RestApi::Request<FJoinGuildRequest>(ShardAPI + "join-guild-request/user-accept" + guildId, "PUT", jsonData, CallbackSuccess, onFailed);
}

void ShardsTech::RejectJoinGuildRequest(FString guildId, FString userId, TFunction<void(FJoinGuildRequest)> onSuccess, TFunction<void()> onFailed)
{
	FAcceptJoinGuildRequestData requestData
	{
		guildId, userId
	};
	FString jsonData;
	FJsonObjectConverter::UStructToJsonObjectString(requestData, jsonData);

	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	RestApi::Request<FJoinGuildRequest>(ShardAPI + "join-guild-request/user-reject" + guildId, "PUT", jsonData, CallbackSuccess, onFailed);
}

void ShardsTech::GetUserHistories(int page, int limit, TFunction<void(FUserHistoryList)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	
	FString url = "transaction-history?";
	url += "limit=" + FString::FromInt(limit);
	url += "&page=" + FString::FromInt(page);
	RestApi::Request<FUserHistoryList>(ShardAPI + url, "GET", "", CallbackSuccess, onFailed);
}

void ShardsTech::GetGuildHistories(int page, int limit, TFunction<void(FGuildHistoryList)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	
	FString url = "transaction-history/guild?";
	url += "limit=" + FString::FromInt(limit);
	url += "&page=" + FString::FromInt(page);
	RestApi::Request<FGuildHistoryList>(ShardAPI + url, "GET", "", CallbackSuccess, onFailed);
}
