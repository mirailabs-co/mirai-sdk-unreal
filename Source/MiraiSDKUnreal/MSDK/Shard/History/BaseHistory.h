#pragma once

#include "BaseHistory.generated.h"

USTRUCT(BlueprintType)
struct FBaseHistory
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "History")
	FString _id;

	UPROPERTY(BlueprintReadWrite, Category = "History")
	FString txHash;

	UPROPERTY(BlueprintReadWrite, Category = "History")
	FString type;

	UPROPERTY(BlueprintReadWrite, Category = "History")
	int64 amount;

	UPROPERTY(BlueprintReadWrite, Category = "History")
	float price;

	UPROPERTY(BlueprintReadWrite, Category = "History")
	FDateTime createdAt;

	UPROPERTY(BlueprintReadWrite, Category = "History")
    TMap<FString, FString> metadata;
};