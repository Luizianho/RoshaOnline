// Fill out your copyright notice in the Description page of Project Settings.


#include "RoshaPlayerState.h"
#include "RequestType.h"
#include "Http.h"




// Wysylam Request do pliczku rosha_login.php
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
    //HttpRequest->OnProcessRequestComplete().BindUObject(this, &ARoshaPlayerState::CreateLoginRequestComplete);
    HttpRequest->ProcessRequest();
}

// Wysylam Request do pliczku rosha_login.php
void ARoshaPlayerState::CreateGetAllCharactersRequest(int32 UserID)
{

    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &ARoshaPlayerState::CreateGetAllcharactersRequestComplete);

    // Link to pliczku PHP
    FString URL = FString::Printf(TEXT("https://403.rosha.online/rosha_GetAllCharacters.php"));
    HttpRequest->SetURL(URL);
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetNumberField(TEXT("userid"), UserID);

    FString JsonString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    HttpRequest->SetContentAsString(JsonString);

    // Wys³anie ¿¹dania
    //HttpRequest->OnProcessRequestComplete().BindUObject(this, &ARoshaPlayerState::CreateGetAllcharactersRequestComplete);
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
                        int32 Local_AccountID;
                        FString Local_Email;

                        if (JsonObject->TryGetNumberField(TEXT("userid"), Local_AccountID) && JsonObject->TryGetStringField(TEXT("email"), Local_Email))
                        {
                            // Logowanie udane
                            UE_LOG(LogTemp, Warning, TEXT("Login successful! User ID: %d, Email: %s"), Local_AccountID, *Local_Email);
                            CreateGetAllCharactersRequest(Local_AccountID);
                            return;
                        }                        
                    }
                    else
                    {
                        //UE_LOG(LogTemp, Warning, TEXT("Invalid login or password"));
                        //return;
                    }
                }
            }
        }
    }

    // Logowanie nieudane lub wyst¹pi³ b³¹d
    //UE_LOG(LogTemp, Error, TEXT("Login failed or error occurred!"));
}

void ARoshaPlayerState::CreateGetAllcharactersRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        // SprawdŸ czy odpowiedŸ jest prawid³owa (status 200)
        if (Response->GetResponseCode() == 200)
        {
            FString ResponseString = Response->GetContentAsString();
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseString);

            if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
            {
                FString Status;
                if (JsonObject->TryGetStringField(TEXT("status"), Status))
                {
                    if (Status == TEXT("OK"))
                    {
                        TArray<FCharacterData> Characters;

                        // Parsowanie odpowiedzi JSON
                        TArray<TSharedPtr<FJsonValue>> CharactersArray = JsonObject->GetArrayField(TEXT("characters"));

                        for (const auto& CharacterValue : CharactersArray)
                        {
                            TSharedPtr<FJsonObject> CharacterObject = CharacterValue->AsObject();

                            // Pobranie ID i Name postaci
                            int32 ID = CharacterObject->GetIntegerField(TEXT("id"));
                            FString Name = CharacterObject->GetStringField(TEXT("name"));

                            // Stworzenie obiektu postaci i dodanie go do tablicy
                            FCharacterData NewCharacter;
                            NewCharacter.ID = ID;
                            NewCharacter.Name = Name;
                            Characters.Add(NewCharacter);

                            // Wyœwietlenie ID i Name postaci za pomoc¹ logu Unreal Engine
                            UE_LOG(LogTemp, Warning, TEXT("Character ID: %d, Name: %s"), ID, *Name);
                        }
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Failed to retrieve status from JSON response."));
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to deserialize JSON response."));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Received response with status code %d"), Response->GetResponseCode());
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to receive valid response."));
    }
}






