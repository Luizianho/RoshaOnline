// Fill out your copyright notice in the Description page of Project Settings.


#include "RoshaGameInstance.h"
#include "Http.h"
#include "Kismet/GameplayStatics.h"

void URoshaGameInstance::GetRoshaIPAddress()
{
	// Tworzê obiekt Request
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();

	// Je¿eli Request sie powiedzie, odpowiedŸ znajdziemy w funkcji HandleRoshaIPComplete();
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &URoshaGameInstance::HandleRoshaIPComplete);

	// Link to pliczku PHP
	FString URL = FString::Printf(TEXT("https://403.rosha.online/rosha_get_ip.php"));
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	// Wysy³amy zapytanie
	HttpRequest->ProcessRequest();
}

void URoshaGameInstance::ConnectToServer(const FString IP)
{
    UGameplayStatics::OpenLevel(this, *IP);
}

void URoshaGameInstance::HandleRoshaIPComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        FString ResponseStr = Response->GetContentAsString();

        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseStr);

        if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
        {
            if (JsonObject->TryGetStringField("status", RoshaStatusPage))
            {
                // Je¿eli w PHP 'status' => 'OK'
                if (RoshaStatusPage.Equals("OK", ESearchCase::IgnoreCase))
                {
                    // Je¿eli w PHP próbujemy pobraæ 'address' => '1.2.3.4'
                    if (JsonObject->TryGetStringField("address", IPAddress))
                    {
                        // Poprawnie pobraliœmy IP
                        UE_LOG(LogTemp, Warning, TEXT("Address: %s"), *IPAddress);
                    }
                    else
                    {
                        // Niepoprawny IP
                        UE_LOG(LogTemp, Warning, TEXT("Invalid address: %s"), *IPAddress);
                    }
                }
                else
                {
                    // B³¹d statusu pliku PHP 'status' != 'OK'
                    UE_LOG(LogTemp, Warning, TEXT("Invalid Status: %s"), *RoshaStatusPage);
                }
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to receive response from server."));
    }
}