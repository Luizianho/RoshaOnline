// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RoshaPlayerState.generated.h"

class IHttpRequest;
class IHttpResponse;

typedef TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> FHttpRequestPtr;
typedef TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> FHttpResponsePtr;

UCLASS()
class ROSHAONLINE_API ARoshaPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	// Enum do wykorzystanai na kiedys
	//UFUNCTION(BlueprintCallable, Category = "DB")
	//void SendRequest(ERequestType RequestType);

	UFUNCTION(BlueprintCallable, Category = "DB")
	void CreateLoginRequest(FString LoginVal, FString PassVal);

	void CreateLoginRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//ERequestType DBRequestType;

	UPROPERTY(BlueprintReadOnly)
	FString LoginName;

	UPROPERTY(BlueprintReadOnly)
	FString PassName;

};
