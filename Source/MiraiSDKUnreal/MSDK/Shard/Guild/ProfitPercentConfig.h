#pragma once
#include "CoreMinimal.h"
#include "ProfitPercentConfig.generated.h"

USTRUCT(BlueprintType)
struct FProfitPercentConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profit Percent")
	float GuildOwnerPercent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profit Percent")
	float FractionsOwnerPercent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profit Percent")
	float SeatsOwnerPercent;
};