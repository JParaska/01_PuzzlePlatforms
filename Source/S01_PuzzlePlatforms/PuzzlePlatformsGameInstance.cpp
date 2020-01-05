// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuWidget.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "MenuSystem/MainMenu.h"

const static FName SESSION_NAME = TEXT("TestSession");
const static FName SERVER_NAME_KEY = TEXT("ServerName");

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance() {
	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MainMenuWidgetClass.Class != nullptr) {
		MainMenuClass = MainMenuWidgetClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> GameMenuWidgetClass(TEXT("/Game/MenuSystem/WBP_GameMenu"));
	if (GameMenuWidgetClass.Class != nullptr) {
		GameMenuClass = GameMenuWidgetClass.Class;
	}
}

void UPuzzlePlatformsGameInstance::Init() {
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr) {
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid()) {
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnSessionCreatedCompleted);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnSessionDestroyedCompleted);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnSessionFindCompleted);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnJoinSessionCompleted);
		}
	}
}

void UPuzzlePlatformsGameInstance::LoadMenu() {
	if (MainMenuClass != nullptr) {
		MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
		if (MainMenu != nullptr) {
			MainMenu->Setup();
			MainMenu->SetMenuInterface(this);
		}
	}
}

void UPuzzlePlatformsGameInstance::LoadGameMenu() {
	if (GameMenuClass != nullptr) {
		UMenuWidget* GameMenu = CreateWidget<UMenuWidget>(this, GameMenuClass);
		if (GameMenu != nullptr) {
			GameMenu->Setup();
			GameMenu->SetMenuInterface(this);
		}
	}
}

void UPuzzlePlatformsGameInstance::Host(const FString ServerName) {
	this->ServerName = ServerName;
	if (SessionInterface.IsValid()) {
		auto NamedSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (NamedSession != nullptr) {
			SessionInterface->DestroySession(SESSION_NAME);
		} else {
			CreateSession();
		}
	}
}

void UPuzzlePlatformsGameInstance::OnSessionDestroyedCompleted(FName SessionName, bool Destroyed) {
	if (Destroyed) {
		CreateSession();
	}
}

void UPuzzlePlatformsGameInstance::CreateSession() {
	if (SessionInterface.IsValid()) {
		FOnlineSessionSettings SessionSettings;

		SessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL"; // Set lan match only if testing with NULL OSS
		SessionSettings.NumPublicConnections = 10;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.Set(SERVER_NAME_KEY, ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UPuzzlePlatformsGameInstance::OnSessionCreatedCompleted(FName SessionName, bool Created) {
	if (Created) {
		UEngine* Engine = GetEngine();
		if (ensure(Engine != nullptr)) {
			Engine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Hosting"));
		}

		UWorld* World = GetWorld();
		if (ensure(World != nullptr)) {
			World->ServerTravel("/Game/ThirdPersonCPP/Maps/LobbyMap?listen");
		}
	}
}

void UPuzzlePlatformsGameInstance::OnSessionFindCompleted(bool Success) {
	UE_LOG(LogTemp, Warning, TEXT("Finding session finished."));
	if (Success && SessionSearch.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("Found %i session/s."), SessionSearch->SearchResults.Num());
		TArray<FServerData> Servers;
		for (const auto & SearchResult : SessionSearch->SearchResults) {
			FServerData Data;
			Data.HostUserName = SearchResult.Session.OwningUserName;
			Data.MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
			Data.CurrentPlayers = Data.MaxPlayers - SearchResult.Session.SessionSettings.NumPublicConnections;
			FString ServerName;
			Data.ServerName = SearchResult.Session.SessionSettings.Get(SERVER_NAME_KEY, ServerName) ? ServerName : SearchResult.GetSessionIdStr();
			Servers.Add(Data);
		}
		if (MainMenu != nullptr) {
			MainMenu->SetServerList(Servers);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Error finding sessions!"));
	}
}

void UPuzzlePlatformsGameInstance::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result) {
	if (SessionInterface.IsValid()) {
		FString ConnectInfo;
		if (SessionInterface->GetResolvedConnectString(SessionName, ConnectInfo)) {
			APlayerController* PlayerController = GetFirstLocalPlayerController();
			if (PlayerController != nullptr) {
				PlayerController->ClientTravel(ConnectInfo, ETravelType::TRAVEL_Absolute);
			}
		}
	}
}

void UPuzzlePlatformsGameInstance::Join(const uint32 SessionIndex) {
	if (SessionInterface.IsValid() && SessionSearch.IsValid()) {
		SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[SessionIndex]);
	}
}

void UPuzzlePlatformsGameInstance::LoadMainMenu() {
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (ensure(PlayerController != nullptr)) {
		PlayerController->ClientTravel("/Game/ThirdPersonCPP/Maps/MainMenuMap", ETravelType::TRAVEL_Absolute);
	}
}

void UPuzzlePlatformsGameInstance::QuitGame() {
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (ensure(PlayerController != nullptr)) {
		PlayerController->ConsoleCommand("quit");
	}
}

void UPuzzlePlatformsGameInstance::GetServerList() {
	if (SessionInterface.IsValid()) {
		SessionSearch = MakeShareable(new FOnlineSessionSearch());
		if (SessionSearch.IsValid()) {
			SessionSearch->bIsLanQuery = true;
			UE_LOG(LogTemp, Warning, TEXT("Finding sessions started..."));
			SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		}
	}
}
