// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MiraiSDKUnreal/MSDK/Shard/Guild/GuildScoreDTO.h"
#include "MyActorTest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateUIDelegate);

UCLASS()
class MIRAISDKUNREAL_API AMyActorTest : public AActor
{
	GENERATED_BODY()
	
public:
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
	void FetchGuilds(FString leaderboardId, FString name, int page, int limit, ESortType sort);
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	void JoinGuild(FString guildId);
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetLeaderboards();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetFirstLeaderboard();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetListGuild();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetMyUserData();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetMyGuildData();
	UFUNCTION(BlueprintCallable, Category = "TestFunc")
	FString GetMyRequestJoinGuild();
	UPROPERTY(BlueprintAssignable, Category = "TestFunc")
	FUpdateUIDelegate UpdateUIDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FGuildScoreDTO GuildScoreDto;
};
