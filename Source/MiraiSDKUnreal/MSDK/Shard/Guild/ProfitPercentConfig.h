#pragma once
#include "CoreMinimal.h"
#include "ProfitPercentConfig.generated.h"

USTRUCT(BlueprintType)
struct FProfitPercentConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profit Percent")
	double GuildOwnerPercent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profit Percent")
	double FractionsOwnerPercent;
	
	double SeatsOwnerPercent() const
	{
		return 1 - GuildOwnerPercent - FractionsOwnerPercent;
	}
	
	FProfitPercentConfig(double guildOwnerPercent = 0, double fractionsOwnerPercent = 0)
	{
		double totalPercent = guildOwnerPercent + fractionsOwnerPercent;
		if (totalPercent > 1.0)
		{
			guildOwnerPercent /= totalPercent;
			fractionsOwnerPercent /= totalPercent;
		}
		GuildOwnerPercent = FMath::RoundToInt(guildOwnerPercent * 100) / 100.0;
		FractionsOwnerPercent = FMath::RoundToInt(fractionsOwnerPercent * 100) / 100.0;
	}
};