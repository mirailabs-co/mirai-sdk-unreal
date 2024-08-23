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
	struct is_array : std::false_type {};

template <typename U>
	struct is_array<TArray<U>> : std::true_type {};

template <typename T>
	struct array_element_type;

template <typename U>
	struct array_element_type<TArray<U>>
	{
		using type = U;
	};
	
template <typename T>
	static void Request(const FString& Url, const FString& method = "GET", const FString& data = "", const FString& selectToken = "",
 		TFunction<void(T)> callbackSuccess = nullptr, TFunction<void()> callbackFailed = nullptr)
	{
		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
		Request->OnProcessRequestComplete().BindLambda([=] (FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			OnResponseReceived<T>(Response, bWasSuccessful, Url, selectToken, callbackSuccess, callbackFailed);
		});
		Request->SetURL(Url);
		Request->SetVerb(method);
	
		Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
		Request->SetHeader("Authorization", "Bearer " + token);
		Request->SetHeader("x-client-id", client_id);
	
		if (data.Len() > 0) // Check if ContentJsonString is not empty()
			Request->SetContentAsString(data);
		Request->ProcessRequest();

		auto log = ">> " + method + " Request: " + Url + " \n" + Request->GetHeader("Authorization");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *log);
	}
	
private:
template <typename T>
	static void OnResponseReceived(FHttpResponsePtr Response, bool bWasSuccessful, FString Url, FString selectToken,
		TFunction<void(T)> callbackSuccess, TFunction<void()> callbackFailed)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			auto result = Response->GetContentAsString();
			UE_LOG(LogTemp, Log, TEXT("Request Response %s: %s"), *Url, *result);

			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(result);
			if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
			{
				int statusCode = 0;
				JsonObject->TryGetNumberField("statusCode", statusCode);
				if (statusCode >= 400) //error code
				{
					if (callbackFailed != nullptr)
						callbackFailed();
					UE_LOG(LogTemp, Error, TEXT("Error %d"), statusCode);
				}
			}
			else
			{
				if (result == "[]") //empty response
				{
					if (callbackFailed != nullptr)
						callbackFailed();
					UE_LOG(LogTemp, Error, TEXT("Empty response"));
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to deserialize JSON"));
				}
			}
			
			T MyValue;
			if (selectToken != "" && JsonObject.IsValid())
			{
				TArray<TSharedPtr<FJsonValue>> tokenValueArr = JsonObject->GetArrayField(selectToken);
				FString tokenJson;
				if (!tokenValueArr.IsEmpty())
				{
					TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&tokenJson);
					FJsonSerializer::Serialize(tokenValueArr, Writer);
				}
				else
				{
					tokenJson = JsonObject->GetStringField(selectToken);
				}
				result = tokenJson;
			}
			if constexpr (std::is_same_v<T, FString>)
			{
				if (callbackSuccess != nullptr)
					callbackSuccess(result);
			}
			else
			if constexpr (std::is_same_v<T, int>)
			{
				if (callbackSuccess != nullptr)
					callbackSuccess(FCString::Atoi(*result));
			}
			else
			if constexpr (is_array<T>::value)
			{
				using ElementType = typename array_element_type<T>::type;
				TArray<TSharedPtr<FJsonValue>> JsonArray;
				TArray<ElementType> array;
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(result);
				// Deserialize the json data given Reader and the actual object to deserialize
		
				if (FJsonSerializer::Deserialize(Reader, JsonArray))
				{
					for (auto jsonElement : JsonArray)
					{
						FString JsonString;
						TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
						FJsonSerializer::Serialize(jsonElement->AsObject().ToSharedRef(), Writer);
				
						ElementType data;
						if (FJsonObjectConverter::JsonObjectStringToUStruct<ElementType>(JsonString, &data))
						{
							array.Add(data);
						}
					}
					if (callbackSuccess != nullptr)
						callbackSuccess(array);
				}
				else
				{
					if (callbackFailed != nullptr)
					callbackFailed();
				}
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