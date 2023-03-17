// Author: Lucas Vilas-Boas
// Year: 2023
// Repo: https://github.com/lucoiso/UEHttpGPT

#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintAsyncActionBase.h>
#include "HttpGPTRequest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHttpGPTGenericDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHttpGPTResponse, const FString&, Response);

/**
 * 
 */
UCLASS(NotPlaceable)
class HTTPGPT_API UHttpGPTRequest : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "AzSpeech")
	FHttpGPTResponse ResponseReceived;

	UPROPERTY(BlueprintAssignable, Category = "AzSpeech")
	FHttpGPTGenericDelegate RequestSent;

	UPROPERTY(BlueprintAssignable, Category = "AzSpeech")
	FHttpGPTGenericDelegate RequestNotSent;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Send GPT Message Async"))
	static UHttpGPTRequest* SendGPTMessageAsync(UObject* WorldContextObject, const FString& Message);

	virtual void Activate() override;

protected:
	FString Message;
	mutable FCriticalSection Mutex;

	virtual void ProcessResponse(const FString& Content, const bool bWasSuccessful);
	FString GetDesserializedResponseString(const FString& Content) const;
};
