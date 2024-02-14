// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyController.h"
#include "RoshaGameInstance.h"

void ALobbyController::BeginPlay()
{
    Super::BeginPlay();

    // Wywo³aj funkcjê GetRoshaIPAddress() z tej klasy PlayerController
    GetRoshaIPAddress();
}

void ALobbyController::GetRoshaIPAddress()
{
    // Uzyskaj dostêp do instancji swojej gry
    URoshaGameInstance* GameInstance = Cast<URoshaGameInstance>(GetGameInstance());
    if (GameInstance)
    {
        // Wywo³aj funkcjê GetRoshaIPAddress() z instancji gry
        GameInstance->GetRoshaIPAddress();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get game instance."));
    }
}