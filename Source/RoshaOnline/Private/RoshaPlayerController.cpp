// Fill out your copyright notice in the Description page of Project Settings.


#include "RoshaPlayerController.h"
#include "RoshaPlayerState.h"

void ARoshaPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ARoshaPlayerController::AuthorizeEnter_Implementation()
{
	ARoshaPlayerState* playerState = GetPlayerState<ARoshaPlayerState>();
	if (playerState)
	{
		playerState->ID = PlayerID;
		playerState->AccID = AccountID;
	}
}


