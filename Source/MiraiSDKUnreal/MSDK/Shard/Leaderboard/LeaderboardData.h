#pragma once

#include "CoreMinimal.h"
#include "LeaderboardData.generated.h"

USTRUCT(BlueprintType)
struct FLeaderboardData
{
GENERATED_BODY()

public:
	UPROPERTY()
	FString _id;
	UPROPERTY()
	FString name;
	UPROPERTY()
	bool isHidden;
};
