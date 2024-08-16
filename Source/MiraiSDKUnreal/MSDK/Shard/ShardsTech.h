#pragma once

#include "CoreMinimal.h"
#include "ShardsTechConfig.h"
#include "Guild/GuildScoreDTO.h"
#include "Guild/MyGuildData.h"
#include "Leaderboard/LeaderboardData.h"
#include "Seat/SellSeatData.h"
#include "User/ShardsTechUser.h"

static FString ShardAPI;

UENUM(BlueprintType)
enum class ShardEnviron : uint8
{
	Dev, Prod
};


UENUM(BlueprintType)
enum class SortType : uint8
{
	asc, desc
};


class ShardsTech
{
public:
	static void Init(ShardEnviron env);
	static FShardsTechUser MyUser;
	static FMyGuildData MyGuild;
	static FSellSeatData MySeatOnSale;
	static FShardsTechConfig GameConfig;
	static TArray<FLeaderboardData> ListLeaderboards;
	
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
	static void GetGuildScores(FString leaderBoardId,FString name="", int page = 1, int limit = 100, SortType sort = SortType::asc,
		TFunction<void(FGuildScoreDTO)> onSuccess = nullptr, TFunction<void()> onFailed = nullptr);

private:
	static void CreateDAppLink();
	static void OpenDAppLink();
	static void WaitAction();
	static void ExecuteAction();
};