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
	result += "MyUserData:\n";
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
	result += "MyGuild:\n";
	result += "Id: " + ShardsTech::MyGuild._id + "\n";
	result += "Name: " + ShardsTech::MyGuild.name + "\n";
	result += "Owner: " + ShardsTech::MyGuild.owner.UserId + "\n";
	result += "TxGuildOwnerShare: " + FString::SanitizeFloat(ShardsTech::MyGuild.txGuildOwnerShare) + "\n";
	result += "GuildOwnerShare: " + FString::SanitizeFloat(ShardsTech::MyGuild.guildOwnerShare) + "\n";
	result += "RewardShareForMembers: " + FString::SanitizeFloat(ShardsTech::MyGuild.rewardShareForMembers) + "\n";
	result += "SeatPrice: " + FString::SanitizeFloat(ShardsTech::MyGuild.seatPrice) + "\n";
	if (ShardsTech::MyGuild.metadata.Contains("desc"))
		result += "Description: " + ShardsTech::MyGuild.metadata["desc"] + "\n";
	result += "Member: \n";
	for (auto member : myGuildMember)
	{
		result += member.UserId + "\n";
	}
	return result;
}

FString AMyActorTest::GetListFraction()
{
	FString result = FString();

	result += "List fraction: \n";

	for (auto fraction : myFractions)
	{
		result += fraction.guild.name + " - " + FString::FromInt(fraction.amount) + "\n";
	}
	
	return result;
}

FString AMyActorTest::GetFractionInfo()
{
	FString result = FString();

	result += "Fraction info: \n";

	result += "My fraction in G: " + FString::FromInt(myFractionsInGuildCount) + "\n";
	result += "Total fraction: " + FString::FromInt(totalFractionInGuild) + "\n";
	result += "Buy price: " + FString::SanitizeFloat(buyFractionsPrice.price) + "\n";
	result += "Sell price: " + FString::SanitizeFloat(sellFractionsPrice.price) + "\n";
	
	return result;
}


FString AMyActorTest::GetUserHistory()
{
	FString result = FString();
	result += "User history:\n";
	for (auto History : UserHistories)
	{
		result += History.type + "\n";
	}
	return result;
}

FString AMyActorTest::GetGuildHistory()
{
	FString result = FString();
	result += "Guild history:\n";
	for (auto History : GuildHistories)
	{
		result += History.User.UserId + " - " + History.type + "\n";
	}
	return result;
}

FString AMyActorTest::GetLeaderboards()
{
	FString result = FString();
	result += "Leaderboards:\n";
	for (auto leaderboard : ShardsTech::ListLeaderboards)
	{
		result += leaderboard._id + " - " + leaderboard.name + "\n";
	}
	return result;
}

FString AMyActorTest::GetListGuild()
{
	FString result = FString();
	result += "List guild:\n";
	for (auto guildData : GuildScoreDto.data)
	{
		result += guildData.guild._id + " - " + guildData.guild.name + "\n";
	}
	return result;
}

FString AMyActorTest::GetMyRequestJoinGuild()
{
	FString result = FString();
	result += "My request:\n";
	int index = 0;
	for (auto request : ShardsTech::ListJoinGuildRequests)
	{
		if (request.status != EJoinStatus::pending) continue;
		index++;
		result += FString::FromInt(index) + ". " + request.guild + " - " + GameUtils::EnumToString(request.status) + "\n";
	}
	return result;
}

void AMyActorTest::AcceptJoinGuildRequest(FString userId)
{
	ShardsTech::AcceptJoinGuildRequest(ShardsTech::MyGuild._id, userId, [this](auto res)
	{
		UpdateUIDelegate.Broadcast();
	});
}

void AMyActorTest::RejectJoinGuildRequest(FString userId)
{
	ShardsTech::RejectJoinGuildRequest(ShardsTech::MyGuild._id, userId, [this](auto res)
	{
		UpdateUIDelegate.Broadcast();
	});
}


FString AMyActorTest::GetGuildRequestJoinGuild()
{
	FString result = FString();
	result += "Guild request:\n";
	int index = 0;
	for (auto request : GuildRequests)
	{
		if (request.status != EJoinStatus::pending) continue;
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
}

void AMyActorTest::Login()
{
	ShardsTech::Init(EShardEnviron::Dev, [this]()
	{
		ShardsTech::Login();
		FetchMyUser(),FetchMyGuild(),FetchMySeatOnSale();
	});
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
	ShardsTech::FetchMySeatOnSale([this](auto res)
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
	ShardsTech::GetJoinGuildRequestsOfGuild(ShardsTech::MyGuild._id, [this](auto res)
	{
		GuildRequests = res;
		UpdateUIDelegate.Broadcast();
	});
	ShardsTech::GetUsersOfGuild(ShardsTech::MyGuild._id, [this](auto res)
	{
		myGuildMember = res;
		UpdateUIDelegate.Broadcast();
	});
}

void AMyActorTest::UpdateUserHistory(int page, int limit)
{
	ShardsTech::GetUserHistories(page, limit, [this](auto res)
	{
		UserHistories = res;
		UpdateUIDelegate.Broadcast();
	});
}

void AMyActorTest::UpdateGuildHistory(int page, int limit)
{
	ShardsTech::GetGuildHistories(page, limit, [this](auto res)
	{
		GuildHistories = res;
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

void AMyActorTest::UpdateGuild(FString name, double slotPrice, double guildOwnerPercent, double fractionsOwnerPercent, FString avatar, FString description)
{
	if (!ShardsTech::IsAllowUpdate())
	{
		UE_LOG(LogTemp, Log, TEXT("Update not allowed"));
		return;
	}
	ShardsTech::UpdateGuild(name, slotPrice, 0.9f, FProfitPercentConfig(guildOwnerPercent, fractionsOwnerPercent), avatar, description, [this]()
	{
		UpdateUIDelegate.Broadcast();
	});
}

void AMyActorTest::DisbandGuild()
{
	if (ShardsTech::MyGuild._id == "")
	{
		UE_LOG(LogTemp, Log, TEXT("not in guild"));
		return;
	}
	ShardsTech::DisbandGuild([this]()
	{
		UpdateUIDelegate.Broadcast();
	});
}

void AMyActorTest::UpdateListFraction(FString guildId)
{
	selectingGuildId = guildId;
	ShardsTech::GetMyFractions([this](auto res)
	{
		myFractions = res;
		UpdateUIDelegate.Broadcast();
	});
	ShardsTech::GetMyFractionsOfGuild(guildId, [this](auto res)
	{
		myFractionsInGuildCount = res;
		UpdateUIDelegate.Broadcast();
	});
	ShardsTech::GetSellFractionsPrice(guildId, 1, [this](auto res)
	{
		buyFractionsPrice = res;
		UpdateUIDelegate.Broadcast();
	});
	ShardsTech::GetBuyFractionsPrice(guildId, 1, [this](auto res)
	{
		sellFractionsPrice = res;
		UpdateUIDelegate.Broadcast();
	});
	ShardsTech::GetTotalFractionsOfGuild(guildId, [this](auto res)
	{
		totalFractionInGuild = res;
		UpdateUIDelegate.Broadcast();
	});
}

void AMyActorTest::BuyFraction(int amount, int index)
{
	ShardsTech::BuyFractions(selectingGuildId, amount, index, [this]()
	{
		UpdateUIDelegate.Broadcast();
	});
}

void AMyActorTest::SellFraction(int amount, int index)
{
	ShardsTech::SellFractions(selectingGuildId, amount, index, [this]()
	{
		UpdateUIDelegate.Broadcast();
	});
}

void AMyActorTest::CreateGuild(FString name, double seatPrice, float guildOwnerPercent, float fractionsOwnerPercent)
{
	TSharedPtr<FJsonObject> metadata = MakeShareable(new FJsonObject);
	metadata->SetStringField("transaction_id", "c7c95d92-1b50-4ca9-bbe9-f0911d92b9e8");
	ShardsTech::CreateGuild(name, seatPrice, metadata, 0.9, FProfitPercentConfig(guildOwnerPercent, fractionsOwnerPercent), [this]()
	{
		UpdateUIDelegate.Broadcast();
		UE_LOG(LogTemp, Log, TEXT("Create guild success"));
	}, [this]()
	{
		UE_LOG(LogTemp, Log, TEXT("Create guild failed"));
	});
}
