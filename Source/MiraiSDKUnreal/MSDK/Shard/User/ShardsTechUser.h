#pragma once

#include "CoreMinimal.h"
#include "VerifiedSocial.h"
#include "ShardsTechUser.generated.h"

USTRUCT(BlueprintType)
struct FShardsTechUser
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ShardsTechUser")
	FString Id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ShardsTechUser")
	FString ClientId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ShardsTechUser")
	FString UserId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ShardsTechUser")
	FString Address;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ShardsTechUser")
	FString Metadata;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ShardsTechUser")
	FDateTime CreatedAt;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ShardsTechUser")
	FVerifiedSocial VerifiedSocial;
};