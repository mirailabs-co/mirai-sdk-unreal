#pragma once

#include "CoreMinimal.h"
#include "ShardsTechConfig.h"
#include "Chat/ChatMessageData.h"
#include "Fraction/FractionsPriceData.h"
#include "Fraction/MyFractionsOfGuildData.h"
#include "Guild/GuildScoreDTO.h"
#include "Guild/MyGuildData.h"
#include "History/GuildHistory.h"
#include "History/GuildHistoryList.h"
#include "History/UserHistory.h"
#include "History/UserHistoryList.h"
#include "JoinRequest/JoinGuildRequest.h"
#include "Leaderboard/LeaderboardData.h"
#include "Referral/ChildReferralData.h"
#include "Seat/SellSeatData.h"
#include "User/ShardsTechUser.h"

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
	static void Init(EShardEnviron env);
	
public: //User
	static FShardsTechUser MyUser;
	static void Login();
	static void Logout();
	static void LinkAddress();
	static void FetchMyUser(TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetUserScores();

public: //History
	static void GetUserHistories(int page = 1, int limit = 100, TFunction<void(FUserHistoryList)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetGuildHistories(int page = 1, int limit = 100, TFunction<void(FGuildHistoryList)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
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
	static void CreateGuild(FString name, double seatPrice, FString metadata, float txGuildOwnerShare,
		float profitGuildOwner, float profitMember);
	static void GetGuildScores(const FString& leaderBoardId, const TArray<FString>& guildIds, TFunction<void(FGuildScoreDTO)> onSuccess, TFunction<void()> onFailed);
	static void GetIndexOfGuildInLeaderboard(const FString& guildId, const FString& leaderBoardId, TFunction<void(int)> onSuccess, TFunction<void()> onFailed);
	static void GetUsersOfGuild(const FString& guildId, TFunction<void(TArray<FShardsTechUser>)> onSuccess, TFunction<void()> onFailed);

public: //GuildOwner
	static void ChangeGuildOwner(const FString& NewOwnerShardsId);
	static void UpdateGuild(const FString& Name, double SeatPrice, float TxGuildOwnerShare, const FProfitPercentConfig& ProfitPercentConfig, const FString& Avatar, const FString& Description);
	static void DisbandGuild();
	static void AcceptJoinGuildRequest(FString guildId, FString userId, TFunction<void(FJoinGuildRequest)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void RejectJoinGuildRequest(FString guildId, FString userId, TFunction<void(FJoinGuildRequest)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);

public: //JoinRequest
	static TArray<FJoinGuildRequest> ListJoinGuildRequests;
	static void CreateJoinGuildRequest(FString guildId, TFunction<void(FJoinGuildRequest)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetJoinGuildRequestsOfUser(TFunction<void(TArray<FJoinGuildRequest>)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetJoinGuildRequestsOfGuild(FString guildId, TFunction<void(TArray<FJoinGuildRequest>)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);

public: //Fraction
	static void GetMyFractions(TFunction<void(const TArray<FMyFractionsOfGuildData>&)> OnSuccess, TFunction<void(const FString& ErrorMessage)> OnError);
	static void GetTotalFractionsOfGuild(const FString& GuildId, TFunction<void(int32)> OnSuccess, TFunction<void(const FString& ErrorMessage)> OnError);
	static void GetMyFractionsOfGuild(const FString& GuildId, TFunction<void(int32)> OnSuccess, TFunction<void(const FString& ErrorMessage)> OnError);
	static void GetBuyFractionsPrice(const FString& GuildId, int64 Amount, TFunction<void(const FFractionsPriceData&)> OnSuccess, TFunction<void(const FString& ErrorMessage)> OnError);
	static void GetSellFractionsPrice(const FString& GuildId, int64 Amount, TFunction<void(const FFractionsPriceData&)> OnSuccess, TFunction<void(const FString& ErrorMessage)> OnError);
	static void BuyFractions(const FString& GuildAddress, int64 Amount, int64 Index, TFunction<void()> OnSuccess, TFunction<void(const FString& ErrorMessage)> OnError);
	static void SellFractions(const FString& GuildAddress, int64 Amount, int64 Index, TFunction<void()> OnSuccess, TFunction<void(const FString& ErrorMessage)> OnError);

public: //Seat
	static FSellSeatData MySeatOnSale;
	static void FetchMySeatOnSale(TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetSeatsOnSale(const FString& guildId = "");
	static void GetBuySeatPrice(const FString& guildId);
	static void BuySeat(const FString& guildAddress, const FString& seller, float price);
	static void SellSeat(float price);
	static void FetchMySeatOnSale();
	static void UpdateSellSeatPrice(const FString& sellSeatId, float price);
	static void CancelSellSeat(const FString& sellSeatId);
	static void BurnSeat();

public: //Referral
	static long ReferralProfit;
	static TArray<FChildReferralData> GetChildrenReferralData();

private:
	static void SetupSocket();
	static void CreateDAppLink();
	static void OpenDAppLink();
	static void WaitAction();
	static void ExecuteAction();
};