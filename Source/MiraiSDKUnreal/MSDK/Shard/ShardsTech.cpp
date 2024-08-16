#include "ShardsTech.h"

#include "Guild/GuildScoreDTO.h"
#include "MiraiSDKUnreal/MSDK/GameUtils.h"
#include "Serialization/JsonSerializable.h"

#include "MiraiSDKUnreal/MSDK/RestApi.h"

FShardsTechUser ShardsTech::MyUser;
FMyGuildData ShardsTech::MyGuild;
FShardsTechConfig ShardsTech::GameConfig;
TArray<FLeaderboardData> ShardsTech::ListLeaderboards;

void ShardsTech::Init(ShardEnviron env)
{
	switch (env)
	{
		case ShardEnviron::Dev:
			ShardAPI = FString("https://api-dev.shards.tech/v1/");
			break;
		case ShardEnviron::Prod:
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
		TArray<TSharedPtr<FJsonValue>> JsonArray;
		TArray<FLeaderboardData> result;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(responeseData);
		// Deserialize the json data given Reader and the actual object to deserialize
		
		if (FJsonSerializer::Deserialize(Reader, JsonArray))
		{
			for (auto jsonElement : JsonArray)
			{
				FString JsonString;
				TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
				FJsonSerializer::Serialize(jsonElement->AsObject().ToSharedRef(), Writer);
				
				FLeaderboardData leaderboardData;
				if (FJsonObjectConverter::JsonObjectStringToUStruct<FLeaderboardData>(JsonString, &leaderboardData))
				{
					result.Add(leaderboardData);
				}
			}
		}
		
		ListLeaderboards = result;
		if (onSuccess != nullptr)
			onSuccess(result);
	};
	RestApi::Request<FString>(ShardAPI + "leader-boards", "GET", "", CallbackSuccess, onFailed);
}


void ShardsTech::GetGuildScores(FString leaderBoardId, FString name, int page, int limit, SortType sort,
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