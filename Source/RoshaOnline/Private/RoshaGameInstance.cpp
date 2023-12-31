#include "RoshaGameInstance.h"
#include "Http.h"

void URoshaGameInstance::HttpPostRequest(FString URL, FString Content)
{
    // Utw�rz obiekt ��dania HTTP
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

    // Ustaw parametry ��dania POST
    HttpRequest->SetVerb("POST");
    HttpRequest->SetURL(URL);
    HttpRequest->SetHeader("Content-Type", "application/json"); // Ustaw odpowiedni nag��wek w zale�no�ci od formatu danych
    HttpRequest->SetContentAsString(Content);

    // Ustaw callback dla zako�czenia ��dania
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &URoshaGameInstance::OnHttpRequestComplete);

    // Wy�lij ��danie
    HttpRequest->ProcessRequest();
}

void URoshaGameInstance::HttpGetRequest(FString URL)
{
    // Utw�rz obiekt ��dania HTTP
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

    // Ustaw parametry ��dania
    HttpRequest->SetVerb("GET");
    HttpRequest->SetURL(URL);
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &URoshaGameInstance::OnHttpRequestComplete);

    // Wy�lij ��danie
    HttpRequest->ProcessRequest();
}

void URoshaGameInstance::OnHttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        // Otrzymana tre�� odpowiedzi
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

