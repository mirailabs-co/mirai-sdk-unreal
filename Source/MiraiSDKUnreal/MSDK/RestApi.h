#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

class RestApi
{
public:
	static FString token;
	static FString client_id;

template <typename T>
	static void Request(const FString& Url, const FString& method = "GET", const FString& data = "",
 		TFunction<void(T)> callbackSuccess = nullptr, TFunction<void()> callbackFailed = nullptr)
	{
		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
		Request->OnProcessRequestComplete().BindLambda([=] (FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			OnResponseReceived<T>(Request, Response, bWasSuccessful, callbackSuccess, callbackFailed);
		});
		Request->SetURL(Url);
		Request->SetVerb(method);
	
		Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
		Request->SetHeader("Authorization", "Bearer " + token);
		Request->SetHeader("x-client-id", client_id);
	
		if (data.Len() > 0) // Check if ContentJsonString is not empty()
			Request->SetContentAsString(data);
		Request->ProcessRequest();

		UE_LOG(LogTemp, Warning, TEXT(">> %s Request: %s"), *method, *Url);
	}
	
private:
template <typename T>
	static void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful,
		TFunction<void(T)> callbackSuccess, TFunction<void()> callbackFailed)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			auto result = Response->GetContentAsString();
			UE_LOG(LogTemp, Log, TEXT("Request Response: %s"), *result);
			// Handle the response data as needed

			// Use FJsonObjectConverter to convert the JSON string to the struct
			T MyValue;
			if constexpr (std::is_same_v<T, FString>)
			{
				if (callbackSuccess != nullptr)
					callbackSuccess(result);
			}
			else
			if (FJsonObjectConverter::JsonObjectStringToUStruct<T>(result, &MyValue))
			{
				if (callbackSuccess != nullptr)
					callbackSuccess(MyValue);
			}
			else
			{
				// The conversion failed, print an error message
				UE_LOG(LogTemp, Error, TEXT("Failed to convert JSON string to struct"));
				if (callbackFailed != nullptr)
					callbackFailed();
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Request failed"));
		}
	}
};