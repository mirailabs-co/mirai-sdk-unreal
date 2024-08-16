#pragma once

#include "CoreMinimal.h"
#include "VerifiedSocial.generated.h"

USTRUCT(BlueprintType)
struct FVerifiedSocial
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Social")
	FString Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Social")
	FString Provider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Social")
	FString SocialId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Social")
	FString Email;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Social")
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Social")
	FString FamilyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Social")
	FString GivenName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Social")
	FString Picture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Social")
	FString Url;

	FString GetUrl() const
	{
		if (Provider.Equals(TEXT("twitter")))
		{
			return FString::Printf(TEXT("https://twitter.com/intent/user?user_id=%s"), *SocialId);
		}
		return TEXT("");
	}
};