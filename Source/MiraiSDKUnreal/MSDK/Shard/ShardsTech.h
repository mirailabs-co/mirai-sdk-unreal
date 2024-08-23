#pragma once

#include "CoreMinimal.h"
#include "ShardsTechConfig.h"
#include "Chat/ChatMessageData.h"
#include "Fraction/FractionsPriceData.h"
#include "Fraction/MyFractionsOfGuildData.h"
#include "Guild/GuildScoreDTO.h"
#include "Guild/MyGuildData.h"
#include "History/GuildHistory.h"
#include "History/UserHistory.h"
#include "JoinRequest/JoinGuildRequest.h"
#include "Leaderboard/LeaderboardData.h"
#include "Seat/SellSeatData.h"
#include "User/ShardsTechUser.h"
#include "User/UserScoresDTO.h"

static FString ShardAPI;

UENUM(BlueprintType)
enum class EShardEnviron : uint8
{
	Dev, Prod
};


UENUM(BlueprintType)
enum class ESortType : uint8
{
	asc, desc
};


class ShardsTech
{
public:
	static FShardsTechConfig GameConfig;
	static void Init(EShardEnviron env, TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	
public: //User
	static FShardsTechUser MyUser;
	static void Login();
	static void Logout();
	static bool IsLinkAddress();
	static void LinkAddress(TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void FetchMyUser(TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetUserScores(FString leaderBoardId, int page = 1, int limit = 100, ESortType sort = ESortType::desc,
		TFunction<void(FUserScoresDTO)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);

public: //History
	static void GetUserHistories(int page = 1, int limit = 100, TFunction<void(TArray<FUserHistory>)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetGuildHistories(int page = 1, int limit = 100, TFunction<void(TArray<FGuildHistory>)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static TArray<FChatMessageData> GetChatHistory(int32 Page = 1, int32 Limit = 100);

public: //Chat
	// static SocketIOUnity* _socketIOChat;
	static void (*OnChatMessage)(const FString& Message);
	static TArray<FString> OnlineUsersMyGuild();
	static void SendChat(const FString& Message);

public: //Guild	
	static FMyGuildData MyGuild;
	static TArray<FLeaderboardData> ListLeaderboards;
	static void GetLeaderboards(TFunction<void(TArray<FLeaderboardData>)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void FetchMyGuild(TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetGuildScores(FString leaderBoardId,FString name="", int page = 1, int limit = 100, ESortType sort = ESortType::asc,
		TFunction<void(FGuildScoreDTO)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void CreateGuild(FString name, double seatPrice, TSharedPtr<FJsonObject> metadata, float txGuildOwnerShare, FProfitPercentConfig profitPercentConfig,
		TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetUsersOfGuild(FString guildId, TFunction<void(TArray<FShardsTechUser>)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static bool IsAllowUpdate();

public: //GuildOwner
	static void ChangeGuildOwner(FString newOwnerShardsId, TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void UpdateGuild(FString name = "", double seatPrice = 0, float txGuildOwnerShare = 0,
			FProfitPercentConfig profitPercentConfig = FProfitPercentConfig(), FString avatar = "", FString description = "",
			TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void DisbandGuild(TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void AcceptJoinGuildRequest(FString guildId, FString userId, TFunction<void(FJoinGuildRequest)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void RejectJoinGuildRequest(FString guildId, FString userId, TFunction<void(FJoinGuildRequest)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);

public: //JoinRequest
	static TArray<FJoinGuildRequest> ListJoinGuildRequests;
	static void CreateJoinGuildRequest(FString guildId, TFunction<void(FJoinGuildRequest)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetJoinGuildRequestsOfUser(TFunction<void(TArray<FJoinGuildRequest>)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetJoinGuildRequestsOfGuild(FString guildId, TFunction<void(TArray<FJoinGuildRequest>)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);

public: //Fraction
	static void GetMyFractions(TFunction<void(TArray<FMyFractionsOfGuildData>)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetTotalFractionsOfGuild(FString guildId, TFunction<void(int)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetMyFractionsOfGuild(FString guildId, TFunction<void(int)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetBuyFractionsPrice(FString guildId, int amount, TFunction<void(FFractionsPriceData)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetSellFractionsPrice(FString guildId, int amount, TFunction<void(FFractionsPriceData)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void BuyFractions(FString guildAddress, long amount, long index = 0, TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void SellFractions(FString guildAddress, long amount, long index = 0, TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);

public: //Seat
	static FSellSeatData MySeatOnSale;
	static void FetchMySeatOnSale(TFunction<void(FSellSeatData)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetSeatsOnSale(FString guildId = "", TFunction<void(TArray<FSellSeatData>)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetBuySeatPrice(FString guildId, TFunction<void(FSellSeatData)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void BuySeat(FString guildAddress, FString seller, double price, TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void SellSeat(float price, TFunction<void(FSellSeatData)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void UpdateSellSeatPrice(FString sellSlotId, double price, TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void CancelSellSeat(FString sellSeatId, TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void BurnSeat(TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);

private:
	static void SetupSocket();
	static void CreateDAppLink(FString type, TSharedPtr<FJsonObject> parameters, TSharedPtr<FJsonObject> metadata,
		TFunction<void(FString, FString)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void OpenDAppLink(FString dAppLink, FString actionId, TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void WaitAction(FString actionId, int loopCount, TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void ExecuteAction(FString type, TSharedPtr<FJsonObject> parameters, TSharedPtr<FJsonObject> metadata,
		TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
};