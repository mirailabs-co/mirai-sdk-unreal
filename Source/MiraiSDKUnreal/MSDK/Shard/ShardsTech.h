#pragma once

#include "CoreMinimal.h"
#include "ShardsTechConfig.h"
#include "Guild/GuildScoreDTO.h"
#include "Guild/MyGuildData.h"
#include "JoinRequest/JoinGuildRequest.h"
#include "Leaderboard/LeaderboardData.h"
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
	static void Init(EShardEnviron env);
	static FShardsTechUser MyUser;
	static FMyGuildData MyGuild;
	static FSellSeatData MySeatOnSale;
	static FShardsTechConfig GameConfig;
	static TArray<FLeaderboardData> ListLeaderboards;
	static TArray<FJoinGuildRequest> ListJoinGuildRequests;
	
public: //User
	static void Login();
	static void Logout();
	static void LinkAddress();

	static void FetchMyUser(TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetUserHistories();

	static void GetUserScores();

public: //Guild	
	static void GetLeaderboards(TFunction<void(TArray<FLeaderboardData>)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void FetchMyGuild(TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void FetchMySeatOnSale(TFunction<void()> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetGuildScores(FString leaderBoardId,FString name="", int page = 1, int limit = 100, ESortType sort = ESortType::asc,
		TFunction<void(FGuildScoreDTO)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void CreateGuild(FString name, double seatPrice, FString metadata, float txGuildOwnerShare,
		float profitGuildOwner, float profitMember);

public: //JoinRequest
	static void CreateJoinGuildRequest(FString guildId, TFunction<void(FJoinGuildRequest)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetJoinGuildRequestsOfUser(TFunction<void(TArray<FJoinGuildRequest>)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void GetJoinGuildRequestsOfGuild(FString guildId, TFunction<void(TArray<FJoinGuildRequest>)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void AcceptJoinGuildRequest(FString guildId, FString userId, TFunction<void(FJoinGuildRequest)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);
	static void RejectJoinGuildRequest(FString guildId, FString userId, TFunction<void(FJoinGuildRequest)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);

private:
	static void CreateDAppLink();
	static void OpenDAppLink();
	static void WaitAction();
	static void ExecuteAction();
};