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
	double totalBuyAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Referral Data")
	double totalBuyPrice = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Referral Data")
	double totalSellAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Referral Data")
	double totalSellPrice = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Referral Data")
	double totalReferralPrice = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Referral Data")
	FShardsTechUser user;
};