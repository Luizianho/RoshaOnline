// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RoshaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROSHAONLINE_API ARoshaPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Server")
	void AuthorizeEnter();

	UPROPERTY()
	int32 AccountID;

	UPROPERTY()
	int32 PlayerID;
	
};
