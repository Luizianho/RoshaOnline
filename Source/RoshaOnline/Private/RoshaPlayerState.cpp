// Fill out your copyright notice in the Description page of Project Settings.


#include "RoshaPlayerState.h"
#include "RequestType.h"
#include "Http.h"

/*
 * na razie z tego nie korzystam
 * 
void ARoshaPlayerState::SendRequest(ERequestType RequestType)
{
    // Tutaj umieœæ implementacjê funkcji SendRequest
    // Na przyk³ad:
    switch (RequestType)
    {
    case ERequestType::Login:
        CreateLoginRequest(LoginName, PassName);
        break;
    case ERequestType::Register:
        break;
    default:
        // Obs³uga innych typów ¿¹dañ
        break;
    }
}
*/

void ARoshaPlayerState::CreateLoginRequest(FString LoginVal, FString PassVal)
{

    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &ARoshaPlayerState::CreateLoginRequestComplete);

    // Link to pliczku PHP
    FString URL = FString::Printf(TEXT("https://403.rosha.online/rosha_login.php"));
    HttpRequest->SetURL(URL);
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField(TEXT("login"), LoginVal);
    JsonObject->SetStringField(TEXT("password"), PassVal);

    FString JsonString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    HttpRequest->SetContentAsString(JsonString);

    // Wys³anie ¿¹dania
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &ARoshaPlayerState::CreateLoginRequestComplete);
    HttpRequest->ProcessRequest();
}

void ARoshaPlayerState::CreateLoginRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        // SprawdŸ czy odpowiedŸ jest prawid³owa (status 200)
        if (Response->GetResponseCode() == 200)
        {
            FString ResponseString = Response->GetContentAsString();
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseString);
            if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
            {
                FString Status;
                if (JsonObject->TryGetStringField(TEXT("status"), Status))
                {
                    if (Status == TEXT("OK"))
                    {
                        // Logowanie udane
                        FString Local_AccountID;
                        FString Local_Email;

                        if (JsonObject->TryGetStringField(TEXT("userid"), Local_AccountID) && JsonObject->TryGetStringField(TEXT("email"), Local_Email))
                        {
                            // Logowanie udane
                            UE_LOG(LogTemp, Warning, TEXT("Login successful! User ID: %s, Email: %s"), *Local_AccountID, *Local_Email);
                            return;
                        }                        
                    }
                    else
                    {
                        UE_LOG(LogTemp, Warning, TEXT("Invalid login or password"));
                        return;
                    }
                }
            }
        }
    }

    // Logowanie nieudane lub wyst¹pi³ b³¹d
    UE_LOG(LogTemp, Error, TEXT("Login failed or error occurred!"));
}
