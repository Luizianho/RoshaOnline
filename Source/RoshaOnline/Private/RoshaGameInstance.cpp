#include "RoshaGameInstance.h"
#include "Http.h"

void URoshaGameInstance::HttpPostRequest(FString URL, FString Content)
{
    // Utwórz obiekt ¿¹dania HTTP
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

    // Ustaw parametry ¿¹dania POST
    HttpRequest->SetVerb("POST");
    HttpRequest->SetURL(URL);
    HttpRequest->SetHeader("Content-Type", "application/json"); // Ustaw odpowiedni nag³ówek w zale¿noœci od formatu danych
    HttpRequest->SetContentAsString(Content);

    // Ustaw callback dla zakoñczenia ¿¹dania
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &URoshaGameInstance::OnHttpRequestComplete);

    // Wyœlij ¿¹danie
    HttpRequest->ProcessRequest();
}

void URoshaGameInstance::HttpGetRequest(FString URL)
{
    // Utwórz obiekt ¿¹dania HTTP
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

    // Ustaw parametry ¿¹dania
    HttpRequest->SetVerb("GET");
    HttpRequest->SetURL(URL);
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &URoshaGameInstance::OnHttpRequestComplete);

    // Wyœlij ¿¹danie
    HttpRequest->ProcessRequest();
}

void URoshaGameInstance::OnHttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        // Otrzymana treœæ odpowiedzi
        FString Content = Response->GetContentAsString();
        
        UE_LOG(LogTemp, Log, TEXT("%s"), *Content);
        //RequestStatus(Content);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Request failed!"));
    }
}

void URoshaGameInstance::RequestStatus(FString status)
{
    if (status == "OK")
    {
        UE_LOG(LogTemp, Log, TEXT("OK!"));
    }

    
}

