// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RoshaPlayerState.generated.h"

USTRUCT(BlueprintType)
struct FCharacterData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 ID;

	UPROPERTY(BlueprintReadWrite)
	FString Name;
};

class IHttpRequest;
class IHttpResponse;

typedef TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> FHttpRequestPtr;
typedef TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> FHttpResponsePtr;

UCLASS()
class ROSHAONLINE_API ARoshaPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	// Wysylam Request do PHP - Logowanie
	UFUNCTION(BlueprintCallable, Category = "DB")
	void CreateLoginRequest(FString LoginVal, FString PassVal);

	// Wysylam Request do PHP - Pobranie listy postaci
	UFUNCTION(BlueprintCallable, Category = "DB")
	void CreateGetAllCharactersRequest(int32 UserID);

	// Otrzymuje Response z PHP - Weryfikacja logowania
	void CreateLoginRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// Otrzymuje Response z PHP - Proba pobrania listy postaci
	void CreateGetAllcharactersRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);


	UPROPERTY(BlueprintReadOnly)
	FString LoginName;

	UPROPERTY(BlueprintReadOnly)
	FString PassName;
};
