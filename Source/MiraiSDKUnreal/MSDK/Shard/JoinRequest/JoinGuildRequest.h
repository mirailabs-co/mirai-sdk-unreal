#pragma once

#include "JoinGuildRequest.generated.h"

UENUM()
enum class EJoinStatus : uint8
{
	pending, 
	accepted,
	rejected
};

USTRUCT(Blueprintable)
struct FJoinGuildRequest
{
	GENERATED_BODY();

public:
	UPROPERTY(BlueprintReadWrite, Category = "FJoinGuildRequest")
	FString _id;
	UPROPERTY(BlueprintReadWrite, Category = "FJoinGuildRequest")
	FString userId;
	UPROPERTY(BlueprintReadWrite, Category = "FJoinGuildRequest")
	FString guild;
	UPROPERTY(BlueprintReadWrite, Category = "FJoinGuildRequest")
	EJoinStatus status;
	UPROPERTY(BlueprintReadWrite, Category = "FJoinGuildRequest")
	FDateTime updatedAt;
};


USTRUCT(Blueprintable)
struct FAcceptJoinGuildRequestData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, Category = "FAcceptJoinGuildRequestData")
	FString GuildId;
	UPROPERTY(BlueprintReadWrite, Category = "FAcceptJoinGuildRequestData")
	FString UserId;
};