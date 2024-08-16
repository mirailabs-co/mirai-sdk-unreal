#pragma once

#include "MiraiSDKUnreal/MSDK/Shard/User/ShardsTechUser.h"
#include "ChildReferralData.generated.h"

USTRUCT(BlueprintType)
struct FChildReferralData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Referral Data")
	FString _id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Referral Data")
	double totalBuyAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Referral Data")
	double totalBuyPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Referral Data")
	double totalSellAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Referral Data")
	double totalSellPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Referral Data")
	double totalReferralPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Referral Data")
	FShardsTechUser user;
};