#include "ShardsTech.h"

#if PLATFORM_WINDOWS
	#include "Windows/WindowsPlatformHttp.h"
#elif PLATFORM_ANDROID
	#include "Android/AndroidPlatformHttp.h"
#elif PLATFORM_IOS
	#include "IOS/IOSPlatformHttp.h"
#endif

#include "Guild/GuildScoreDTO.h"
#include "History/UserHistory.h"
#include "MiraiSDKUnreal/MSDK/GameUtils.h"
#include "Serialization/JsonSerializable.h"

#include "MiraiSDKUnreal/MSDK/RestApi.h"
#include "User/UserScoresDTO.h"

FShardsTechUser ShardsTech::MyUser;
FMyGuildData ShardsTech::MyGuild;
FShardsTechConfig ShardsTech::GameConfig;
TArray<FLeaderboardData> ShardsTech::ListLeaderboards;
TArray<FJoinGuildRequest> ShardsTech::ListJoinGuildRequests;

void ShardsTech::Init(EShardEnviron env, TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	switch (env)
	{
		case EShardEnviron::Dev:
			ShardAPI = FString("https://api-dev.shards.tech/v1/");
			break;
		case EShardEnviron::Prod:
			break;
	}
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		GameConfig = responeseData;
		if (onSuccess != nullptr)
			onSuccess();
	};
	RestApi::Request<FShardsTechConfig>(ShardAPI + "game-config", "GET", "", "", CallbackSuccess, onFailed);
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
		if (onSuccess != nullptr)
			onSuccess();
	};
	RestApi::Request<FShardsTechUser>(ShardAPI + "users", "GET", "", "", CallbackSuccess, onFailed);
}

void ShardsTech::FetchMyGuild(TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		MyGuild = responeseData;
		if (onSuccess != nullptr)
			onSuccess();
	};
	RestApi::Request<FMyGuildData>(ShardAPI + "guilds/guild-of-user", "GET", "", "", CallbackSuccess, onFailed);
}
void ShardsTech::FetchMySeatOnSale(TFunction<void(FSellSeatData)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	RestApi::Request<FSellSeatData>(ShardAPI + "user-sell-guild/my", "GET", "", "", CallbackSuccess, onFailed);
}

void ShardsTech::GetLeaderboards(TFunction<void(TArray<FLeaderboardData>)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		ListLeaderboards = responeseData;
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	RestApi::Request<TArray<FLeaderboardData>>(ShardAPI + "leader-boards", "GET", "", "", CallbackSuccess, onFailed);
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


	RestApi::Request<FGuildScoreDTO>(ShardAPI + url, "GET", "", "", CallbackSuccess, onFailed);
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
	RestApi::Request<FJoinGuildRequest>(ShardAPI + "join-guild-request/" + guildId, "POST", "", "", CallbackSuccess, onFailed);
}

void ShardsTech::GetJoinGuildRequestsOfUser(TFunction<void(TArray<FJoinGuildRequest>)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		ListJoinGuildRequests = responeseData;
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	RestApi::Request<TArray<FJoinGuildRequest>>(ShardAPI + "join-guild-request", "GET", "", "", CallbackSuccess, onFailed);
}

void ShardsTech::GetJoinGuildRequestsOfGuild(FString guildId, TFunction<void(TArray<FJoinGuildRequest>)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	RestApi::Request<TArray<FJoinGuildRequest>>(ShardAPI + "join-guild-request/" + guildId, "GET", "", "", CallbackSuccess, onFailed);
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
	RestApi::Request<FJoinGuildRequest>(ShardAPI + "join-guild-request/user-accept", "PUT", jsonData, "", CallbackSuccess, onFailed);
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
	RestApi::Request<FJoinGuildRequest>(ShardAPI + "join-guild-request/user-reject", "PUT", jsonData, "", CallbackSuccess, onFailed);
}

void ShardsTech::GetUserHistories(int page, int limit, TFunction<void(TArray<FUserHistory>)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	
	FString url = "transaction-history?";
	url += "limit=" + FString::FromInt(limit);
	url += "&page=" + FString::FromInt(page);
	RestApi::Request<TArray<FUserHistory>>(ShardAPI + url, "GET", "", "data", CallbackSuccess, onFailed);
}

void ShardsTech::GetGuildHistories(int page, int limit, TFunction<void(TArray<FGuildHistory>)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	
	FString url = "transaction-history/guild?";
	url += "limit=" + FString::FromInt(limit);
	url += "&page=" + FString::FromInt(page);
	RestApi::Request<TArray<FGuildHistory>>(ShardAPI + url, "GET", "", "data", CallbackSuccess, onFailed);
}

void ShardsTech::GetUserScores(FString leaderBoardId, int page, int limit, ESortType sort,
	TFunction<void(FUserScoresDTO)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	
	FString url = "user-score?";
	url += "leaderBoardId=" + leaderBoardId;
	url += "&page=" + page;
	url += "&limit=" + limit;
	url += "&sort=" + GameUtils::EnumToString(sort);
	RestApi::Request<FUserScoresDTO>(ShardAPI + url, "GET", "", "", CallbackSuccess, onFailed);
}

void ShardsTech::GetMyFractions(TFunction<void(TArray<FMyFractionsOfGuildData>)> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		if (onSuccess != nullptr)
			onSuccess(responeseData);
	};
	
	RestApi::Request<TArray<FMyFractionsOfGuildData>>(ShardAPI + "guilds/share/user", "GET", "", "", CallbackSuccess, onFailed);
}

void ShardsTech::GetTotalFractionsOfGuild(FString guildId, TFunction<void(int)> onSuccess, TFunction<void()> onFailed)
{
	RestApi::Request<int>(ShardAPI + "guilds/" + guildId, "GET", "", "", onSuccess, onFailed);
}

void ShardsTech::GetMyFractionsOfGuild(FString guildId, TFunction<void(int)> onSuccess, TFunction<void()> onFailed)
{
	RestApi::Request<int>(ShardAPI + "guilds/user/" + guildId, "GET", "", "", onSuccess, onFailed);
}

void ShardsTech::GetBuyFractionsPrice(FString guildId, int amount, TFunction<void(FFractionsPriceData)> onSuccess, TFunction<void()> onFailed)
{
	RestApi::Request<FFractionsPriceData>(ShardAPI + "guilds/share-price/" + guildId + "/" + FString::FromInt(amount),
		"GET", "", "", onSuccess, onFailed);
}

void ShardsTech::GetSellFractionsPrice(FString guildId, int amount, TFunction<void(FFractionsPriceData)> onSuccess, TFunction<void()> onFailed)
{
	RestApi::Request<FFractionsPriceData>(ShardAPI + "guilds/sell-share-price/" + guildId + "/" + FString::FromInt(amount),
		"GET", "", "", onSuccess, onFailed);
}

void ShardsTech::GetSeatsOnSale(FString guildId, TFunction<void(TArray<FSellSeatData>)> onSuccess, TFunction<void()> onFailed)
{
	FString url = "user-sell-guild/";
	if (guildId == "") url += "list";
	else url += guildId;
	RestApi::Request<TArray<FSellSeatData>>(ShardAPI + url, "GET", "", "", onSuccess, onFailed);
}

void ShardsTech::GetBuySeatPrice(FString guildId, TFunction<void(FSellSeatData)> onSuccess, TFunction<void()> onFailed)
{
	RestApi::Request<FSellSeatData>(ShardAPI + "user-sell-guild/slot-price/" + guildId,
		"GET", "", "", onSuccess, onFailed);
}

void ShardsTech::UpdateSellSeatPrice(FString sellSlotId, double price, TFunction<void()> onSuccess, TFunction<void()> onFailed)
{	
	FUpdateSellSeatPriceRequestData requestData =
	{
		sellSlotId,
		price,
	};
	FString jsonData;
	FJsonObjectConverter::UStructToJsonObjectString(requestData, jsonData);
	
	auto CallbackSuccess = [onSuccess](auto responeseData)
	{
		if (onSuccess != nullptr)
			onSuccess();
	};
	
	RestApi::Request<FString>(ShardAPI + "member/sell-slot", "PUT", jsonData, "", CallbackSuccess, onFailed);
}

void ShardsTech::CancelSellSeat(FString sellSeatId, TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess, onFailed](auto responeseData)
	{
		ShardsTech::FetchMySeatOnSale([onSuccess, onFailed](auto res)
		{
			ShardsTech::FetchMyGuild(onSuccess, onFailed);
		}, onFailed);
	};
	RestApi::Request<FString>(ShardAPI + "member/sell-slot/" + sellSeatId, "DELETE", "", "", CallbackSuccess, onFailed);
}

void ShardsTech::BurnSeat(TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess, onFailed](auto responeseData)
	{
		ShardsTech::FetchMyGuild(onSuccess, onFailed);
	};
	RestApi::Request<FString>(ShardAPI + "member/sell-slot/burn/" + MyGuild._id, "DELETE", "", "", CallbackSuccess, onFailed);
}

void ShardsTech::UpdateGuild(FString name, double slotPrice, float txGuildOwnerShare, FProfitPercentConfig profitPercentConfig, FString avatar, FString description, TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
    TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);
	
	if (name != "") data->SetStringField("name", name);
	if (slotPrice > 0) data->SetNumberField("slotPrice", slotPrice);
	if (txGuildOwnerShare > 0) data->SetNumberField("txGuildOwnerShare", txGuildOwnerShare);
	if (profitPercentConfig.GuildOwnerPercent > 0 && profitPercentConfig.FractionsOwnerPercent > 0)
	{
		auto rewardForMem = 1 - profitPercentConfig.FractionsOwnerPercent;
		data->SetNumberField("rewardShareForMember", rewardForMem);
		data->SetNumberField("guildOwnerShare", profitPercentConfig.GuildOwnerPercent / rewardForMem);
	}
	if (avatar != "") data->SetStringField("avatar", avatar);
	if (description != "") data->SetStringField("description", description);

	FString jsonData;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&jsonData);
	FJsonSerializer::Serialize(data.ToSharedRef(), Writer);
	
	auto CallbackSuccess = [onSuccess, onFailed](auto responeseData)
	{
		ShardsTech::FetchMyGuild(onSuccess, onFailed);
	};
	
	RestApi::Request<FString>(ShardAPI + "guilds/" + MyGuild._id, "PUT", jsonData, "", CallbackSuccess, onFailed);
}

void ShardsTech::GetUsersOfGuild(FString guildId, TFunction<void(TArray<FShardsTechUser>)> onSuccess, TFunction<void()> onFailed)
{
	RestApi::Request<TArray<FShardsTechUser>>(ShardAPI + "guilds/users/" + guildId, "GET", "", "", onSuccess, onFailed);
}

bool ShardsTech::IsAllowUpdate()
{
	if (MyGuild._id == "") return false;
	return MyGuild.numberAllowUpdate > 0 &&
		GameUtils::GetCurrentUTCTimestamp() <= MyGuild.EndAllowUpdateTimestamp &&
		GameUtils::GetCurrentUTCTimestamp() >= MyGuild.StartAllowUpdateTimestamp;
}

void ShardsTech::CreateGuild(FString name, double seatPrice, TSharedPtr<FJsonObject> metadata, float txGuildOwnerShare, FProfitPercentConfig profitPercentConfig,
	TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	auto rewardShareForMembers= 1 - profitPercentConfig.FractionsOwnerPercent;
	auto guildOwnerShare = profitPercentConfig.GuildOwnerPercent / rewardShareForMembers;
	
	TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);
	data->SetStringField("name", name);
	data->SetNumberField("slotPrice", seatPrice);
	data->SetNumberField("rewardShareForMembers", rewardShareForMembers);
	data->SetNumberField("txGuildOwnerShare", txGuildOwnerShare);
	data->SetNumberField("guildOwnerShare", guildOwnerShare);

	auto CallbackSuccess = [onSuccess]()
	{
		ShardsTech::FetchMyGuild(onSuccess);
	};
	ExecuteAction("create-guild", data, metadata, CallbackSuccess, onFailed);
}

void ShardsTech::CreateDAppLink(FString type, TSharedPtr<FJsonObject> parameters, TSharedPtr<FJsonObject> metadata,
		TFunction<void(FString, FString)> onSuccess, TFunction<void()> onFailed)
{
	TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);
	data->SetStringField("type", type);
	if (metadata != nullptr)
		data->SetObjectField("metadata", metadata);

	FString jsonData;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&jsonData);
	FJsonSerializer::Serialize(data.ToSharedRef(), Writer);

	auto CallbackSuccessAction = [onSuccess, onFailed, parameters, type](auto actionId)
	{
		TSharedPtr<FJsonObject> qParams = MakeShareable(new FJsonObject);
		for (auto pair : parameters->Values)
		{
			qParams->SetField(pair.Key, pair.Value);
		}
		qParams->SetStringField("gameId", GameConfig.clientId);
		qParams->SetStringField("actionId", actionId);
		
		auto CreateLink = [qParams, type, onSuccess, onFailed, actionId]()
		{
			auto dAppUrl = GameConfig.linkDapp;
			if (type != "create-guild")
			{
				dAppUrl += "/" + type;
			}
			dAppUrl += "/";


			FString strParams = "";
			for (auto pair : qParams->Values)
			{
				FString urlEncoded = FPlatformHttp::UrlEncode(pair.Value->AsString()).Replace(TEXT("+"), TEXT("%20"));
				strParams += pair.Key + "=" + urlEncoded;
				strParams += "&";
			}
			auto dAppLink = dAppUrl + "?" + strParams;
	
			UE_LOG(LogTemp, Log, TEXT("DAppLink: %s"), *dAppLink);

			if (onSuccess != nullptr)
				onSuccess(dAppLink, actionId);
		};
		
		if (IsLinkAddress())
		{
			qParams->SetStringField("address", MyUser.Address);
			
			TSharedPtr<FJsonObject> genHashData = MakeShareable(new FJsonObject);
			genHashData->SetObjectField("@params", qParams);

			FString jsonHash;
			TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&jsonHash);
			FJsonSerializer::Serialize(genHashData.ToSharedRef(), Writer);
			
			RestApi::Request<FString>("actions/generate-hash", "POST", jsonHash, "",
				[CreateLink, onSuccess, qParams](auto responeseData)
			{
				qParams->SetStringField("hash", responeseData);
				CreateLink();
			}, onFailed);
		}
		else
		{
			CreateLink();
		}
	};
	RestApi::Request<FString>(ShardAPI + "actions", "POST", jsonData, "_id", CallbackSuccessAction, onFailed);
}

void ShardsTech::ExecuteAction(FString type, TSharedPtr<FJsonObject> parameters, TSharedPtr<FJsonObject> metadata,
		TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	auto CallbackSuccess = [onSuccess, onFailed](auto dappLink, auto actionId)
	{
		ShardsTech::OpenDAppLink(dappLink, actionId, onSuccess, onFailed);
	};
	CreateDAppLink(type, parameters, metadata, CallbackSuccess, onFailed);
}

void ShardsTech::OpenDAppLink(FString dappLink, FString actionId, TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	FPlatformProcess::LaunchURL(*dappLink, nullptr, nullptr);
	AsyncTask(ENamedThreads::AnyThread, [actionId, onSuccess, onFailed]()
	{
		auto CallbackSuccess = [onSuccess]()
		{
			if (onSuccess != nullptr)
				onSuccess();
		};
		WaitAction(actionId, 0, CallbackSuccess, onFailed);
	});
}

bool ShardsTech::IsLinkAddress()
{
	return false;
}

void ShardsTech::WaitAction(FString actionId, int loopCount, TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	if (loopCount >= 3000)
	{
		onFailed();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("WaitAction: %s %d"), *actionId, loopCount);
		auto CallbackSuccess = [onSuccess, onFailed, actionId, loopCount](auto status)
		{
			if (status == "success")
			{
				if (onSuccess != nullptr)
					onSuccess();
			}
			else
			if (status == "error")
			{
				if (onSuccess != nullptr)
					onFailed();
			}
			else
			{
				WaitAction(actionId, loopCount + 1, onSuccess, onFailed);
			}
		};
		RestApi::Request<FString>(ShardAPI + "actions/" + actionId, "GET", "", "status", CallbackSuccess, onFailed);
	}
}

void ShardsTech::LinkAddress(TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);
	data->SetStringField("userId", MyUser.UserId);
	
	ShardsTech::ExecuteAction(ShardAPI + "link-address", data, nullptr, onSuccess, onFailed);
}

void ShardsTech::ChangeGuildOwner(FString newOwnerShardsId, TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);
	data->SetStringField("oldOwnerUserId", MyGuild.owner.UserId);
	data->SetStringField("newOwnerId", newOwnerShardsId);
	data->SetStringField("guildAddress", MyGuild.address);
	
	TSharedPtr<FJsonObject> metadata = MakeShareable(new FJsonObject);
	metadata->SetStringField("newOwnerId", newOwnerShardsId);
	metadata->SetStringField("guildAddress", MyGuild.address);

	auto CallbackSuccess = [onSuccess]()
	{
		FetchMyGuild(onSuccess);
	};
	ShardsTech::ExecuteAction("change-guild-owner", data, metadata, CallbackSuccess, onFailed);
}

void ShardsTech::BuySeat(FString guildAddress, FString seller, double price, TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);
	data->SetStringField("guildAddress", guildAddress);
	
	TSharedPtr<FJsonObject> metadata = MakeShareable(new FJsonObject);
	metadata->SetStringField("guildAddress", guildAddress);
	metadata->SetStringField("seller", seller);
	metadata->SetNumberField("price", price);
	
	auto CallbackSuccess = [onSuccess]()
	{
		FetchMyGuild(onSuccess);
	};
	ShardsTech::ExecuteAction("buy-slot", data, metadata, CallbackSuccess, onFailed);
}

void ShardsTech::SellSeat(float price, TFunction<void(FSellSeatData)> onSuccess, TFunction<void()> onFailed)
{
	TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);
	data->SetStringField("guildId", MyGuild._id);
	data->SetNumberField("price", price);
	FString jsonData;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&jsonData);
	FJsonSerializer::Serialize(data.ToSharedRef(), Writer);
	
	auto CallbackSuccess = [onSuccess, onFailed](auto responeseData)
	{
		auto CallbackSuccess = [onSuccess, onFailed]()
		{
			FetchMySeatOnSale(onSuccess, onFailed);
		};
		FetchMyGuild(CallbackSuccess);
	};
	RestApi::Request<FString>(ShardAPI + "member/sell-seat", "POST", jsonData, "", CallbackSuccess, onFailed);
}

void ShardsTech::DisbandGuild(TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);
	data->SetStringField("guildAddress", MyGuild.address);

	auto CallbackSuccess = [onSuccess]()
	{
		FetchMyGuild(onSuccess);
	};
	ExecuteAction("disband-guild", data, nullptr, CallbackSuccess, onFailed);
}

void ShardsTech::BuyFractions(FString guildAddress, long amount, long index, TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);
	data->SetStringField("guildAddress", guildAddress);
	data->SetNumberField("amount", amount);
	data->SetNumberField("index", index);
	
	ExecuteAction("buy-share", data, nullptr, onSuccess, onFailed);
}

void ShardsTech::SellFractions(FString guildAddress, long amount, long index, TFunction<void()> onSuccess, TFunction<void()> onFailed)
{
	TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);
	data->SetStringField("guildAddress", guildAddress);
	data->SetNumberField("amount", amount);
	data->SetNumberField("index", index);
	
	ExecuteAction("sell-share", data, nullptr, onSuccess, onFailed);
}
