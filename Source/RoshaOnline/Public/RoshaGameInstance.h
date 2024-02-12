// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RoshaGameInstance.generated.h"

class IHttpRequest;
class IHttpResponse;

typedef TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> FHttpRequestPtr;
typedef TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> FHttpResponsePtr;


UCLASS()
class ROSHAONLINE_API URoshaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Request")
	void GetRoshaIPAddress();

	void HandleRoshaIPComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString IPAddress;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString RoshaStatusPage;
};
