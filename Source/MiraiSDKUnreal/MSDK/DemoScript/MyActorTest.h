// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MiraiSDKUnreal/MSDK/Shard/Fraction/FractionsPriceData.h"
#include "MiraiSDKUnreal/MSDK/Shard/Fraction/MyFractionsOfGuildData.h"
#include "MiraiSDKUnreal/MSDK/Shard/Guild/GuildScoreDTO.h"
#include "MiraiSDKUnreal/MSDK/Shard/History/GuildHistory.h"
#include "MiraiSDKUnreal/MSDK/Shard/History/UserHistory.h"
#include "MiraiSDKUnreal/MSDK/Shard/JoinRequest/JoinGuildRequest.h"
#include "MyActorTest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateUIDelegate);

UCLASS()
class MIRAISDKUNREAL_API AMyActorTest : public AActor
{
	GENERATED_BODY()
	
public:
	TArray<FMyFractionsOfGuildData> myFractions;
	TArray<FShardsTechUser> myGuildMember;
	int myFractionsInGuildCount, totalFractionInGuild;
	FFractionsPriceData buyFractionsPrice, sellFractionsPrice;	

	// Sets default values for this actor's properties
	AMyActorTest();
	
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void Login();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void Logout();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void UpdateToken(FString value);
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void FetchMyUser();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void FetchMyGuild();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void FetchMySeatOnSale();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void AcceptJoinGuildRequest(FString userId);
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void RejectJoinGuildRequest(FString userId);
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void FetchGuilds(FString leaderboardId, FString name, int page, int limit, ESortType sort);
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void JoinGuild(FString guildId);
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetLeaderboards();

	TArray<FUserHistory> UserHistories;
	TArray<FGuildHistory> GuildHistories;
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void UpdateUserHistory(int page, int limit);
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void UpdateGuildHistory(int page, int limit);
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetUserHistory();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetGuildHistory();

	TArray<FJoinGuildRequest> GuildRequests;
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetFirstLeaderboard();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetListGuild();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetMyUserData();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetMyGuildData();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void UpdateListFraction(FString guildId);
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetListFraction();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetMyRequestJoinGuild();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetGuildRequestJoinGuild();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetFractionInfo();
	UPROPERTY(BlueprintAssignable, Category = "TestFunc")
	FUpdateUIDelegate UpdateUIDelegate;
	
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void UpdateGuild(FString name, double slotPrice, double guildOwnerPercent, double fractionsOwnerPercent, FString avatar, FString description);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FGuildScoreDTO GuildScoreDto;
};
