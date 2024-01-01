// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"


#include "RoshaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ROSHAONLINE_API URoshaGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    // GET!!!!!!!!!!!
    UFUNCTION(BlueprintCallable, Category = "HTTP")
    void HttpGetRequest(FString URL);

    // POST!!!!!!!!!!
    UFUNCTION(BlueprintCallable, Category = "HTTP")
    void HttpPostRequest(FString URL, FString Content);

    // Callback dla zakoñczenia ¿¹dania HTTP
    void OnHttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

    UFUNCTION(BlueprintCallable, Category = "HTTP")
    void RequestStatus(FString status);

    UPROPERTY()
    FString getIP = "https://403.rosha.online/";

};
