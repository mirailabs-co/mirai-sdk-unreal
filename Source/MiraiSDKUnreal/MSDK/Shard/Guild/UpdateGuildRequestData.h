#pragma once

#include "CoreMinimal.h"
#include "UpdateGuildRequestData.generated.h"

USTRUCT(BlueprintType)
struct FUpdateGuildRequestData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TOptional<FString> name;
	UPROPERTY()
	TOptional<double> slotPrice;
	UPROPERTY()
	TOptional<float> txGuildOwnerShare;
	UPROPERTY()
	TOptional<double> rewardShareForMembers;
	UPROPERTY()
	TOptional<double> guildOwnerShare;
	UPROPERTY()
	TOptional<FString> avatar;
	UPROPERTY()
	TOptional<FString> description;
};