// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorTest.h"

#include "MiraiSDKUnreal/MSDK/GameUtils.h"
#include "MiraiSDKUnreal/MSDK/RestApi.h"
#include "MiraiSDKUnreal/MSDK/Shard/ShardsTech.h"


// Sets default values
AMyActorTest::AMyActorTest()
{
}

FString AMyActorTest::GetMyUserData()
{
	FString result = FString();
	result += "Id: " + ShardsTech::MyUser.Id + "\n";
	result += "ClientId: " + ShardsTech::MyUser.ClientId + "\n";
	result += "UserId: " + ShardsTech::MyUser.UserId + "\n";
	result += "Address: " + ShardsTech::MyUser.Address + "\n";
	result += "Metadata: " + ShardsTech::MyUser.Metadata + "\n";
	result += "CreateAt " + ShardsTech::MyUser.CreatedAt.ToString() + "\n";
	return result;
}

FString AMyActorTest::GetMyGuildData()
{
	FString result = FString();
	result += "Id: " + ShardsTech::MyGuild._id + "\n";
	result += "MemberCount: " + FString::FromInt(ShardsTech::MyGuild.userCount) + "\n";
	result += "SeatPrice: " + FString::FromInt(ShardsTech::MyGuild.seatPrice) + "\n";
	result += "Owner: " + ShardsTech::MyGuild.owner.UserId + "\n";
	return result;
}

FString AMyActorTest::GetLeaderboards()
{
	FString result = FString();
	for (auto leaderboard : ShardsTech::ListLeaderboards)
	{
		result += leaderboard._id + " - " + leaderboard.name + "\n";
	}
	return result;
}

FString AMyActorTest::GetListGuild()
{
	FString result = FString();
	for (auto guildData : GuildScoreDto.data)
	{
		result += guildData.guild._id + " - " + guildData.guild.name + "\n";
	}
	return result;
}

FString AMyActorTest::GetMyRequestJoinGuild()
{
	FString result = FString();
	int index = 0;
	for (auto request : ShardsTech::ListJoinGuildRequests)
	{
		index++;
		result += FString::FromInt(index) + ". " + request.guild + " - " + GameUtils::EnumToString(request.status) + "\n";
	}
	return result;
}

FString AMyActorTest::GetFirstLeaderboard()
{
	return FString(ShardsTech::ListLeaderboards[0]._id);
}


// Called when the game starts or when spawned
void AMyActorTest::BeginPlay()
{
	Super::BeginPlay();
	ShardsTech::Init(EShardEnviron::Dev);
}

void AMyActorTest::Login()
{
	ShardsTech::Login();

	FetchMyUser(),FetchMyGuild(),FetchMySeatOnSale();
}

void AMyActorTest::Logout()
{
	ShardsTech::Logout();
}

void AMyActorTest::UpdateToken(FString value)
{
	RestApi::token = value;
	UE_LOG(LogTemp, Log, TEXT("Token update: %s"), *RestApi::token);
}

void AMyActorTest::FetchMyUser()
{
	ShardsTech::FetchMyUser([this]()
	{
		UpdateUIDelegate.Broadcast();
	});
}
void AMyActorTest::FetchMyGuild()
{
	ShardsTech::FetchMyGuild([this]()
	{
		UpdateUIDelegate.Broadcast();
	});
	ShardsTech::GetLeaderboards([this](auto responeseData)
	{
		for (auto leaderboard : responeseData)
		{
			UE_LOG(LogTemp, Log, TEXT("LB name: %s"), *leaderboard.name);
		}
	});
}
void AMyActorTest::FetchMySeatOnSale()
{
	ShardsTech::FetchMySeatOnSale([this]()
	{
		UpdateUIDelegate.Broadcast();
	});
}

void AMyActorTest::FetchGuilds(FString leaderboardId, FString nameFilter, int page, int limit, ESortType sort)
{
	ShardsTech::GetLeaderboards([this](auto res)
	{
		UpdateUIDelegate.Broadcast();
	});
	ShardsTech::GetGuildScores(leaderboardId, nameFilter, page, limit, sort, [this](auto res)
	{
		GuildScoreDto = res;
		UpdateUIDelegate.Broadcast();
	});
	ShardsTech::GetJoinGuildRequestsOfUser([this](auto res)
	{
		UpdateUIDelegate.Broadcast();
	});
}

void AMyActorTest::JoinGuild(FString guildId)
{
	ShardsTech::CreateJoinGuildRequest(guildId, [this](auto res)
	{
		UpdateUIDelegate.Broadcast();
	});
}
