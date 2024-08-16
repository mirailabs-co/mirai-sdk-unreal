#pragma once

#include "MiraiSDKUnreal/MSDK/Shard/Guild/GuildData.h"
#include "MyFractionsOfGuildData.generated.h"

USTRUCT(BlueprintType)
struct FMyFractionsOfGuildData
{
	GENERATED_BODY()

	UPROPERTY()
	FGuildData guild;
	UPROPERTY()
	float amount;
};
