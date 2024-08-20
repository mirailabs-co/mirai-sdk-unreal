#pragma once

#include "CoreMinimal.h"
#include "MiraiSDKUnreal/MSDK/Shard/Guild/GuildData.h"
#include "MiraiSDKUnreal/MSDK/Shard/User/ShardsTechUser.h"
#include "SellSeatData.generated.h"

USTRUCT(BlueprintType)
struct FSellSeatData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sell Seat Data")
	FString _id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sell Seat Data")
	FGuildData guild;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sell Seat Data")
	FString seller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sell Seat Data")
	FShardsTechUser user;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sell Seat Data")
	FString clientId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sell Seat Data")
	float price = 0;
};

USTRUCT(BlueprintType)
struct FUpdateSellSeatPriceRequestData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Update Sell Seat Data")
	FString sellSlotId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Update Sell Seat Data")
	double price;
};