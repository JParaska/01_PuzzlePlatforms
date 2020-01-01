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
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

const static FName SESSION_NAME = TEXT("TestSession");

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

			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			if (SessionSearch.IsValid()) {
				UE_LOG(LogTemp, Warning, TEXT("Finding sessions started..."))
				SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
			}
		}
	}
}

void UPuzzlePlatformsGameInstance::LoadMenu() {
	if (MainMenuClass != nullptr) {
		UMenuWidget* MainMenu = CreateWidget<UMenuWidget>(this, MainMenuClass);
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

void UPuzzlePlatformsGameInstance::Host() {
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
			World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
		}
	}
}

void UPuzzlePlatformsGameInstance::OnSessionFindCompleted(bool Success) {
	UE_LOG(LogTemp, Warning, TEXT("Finding session finished."));
}

void UPuzzlePlatformsGameInstance::Join(const FString & Address) {
	UEngine* Engine = GetEngine();
	if (ensure(Engine != nullptr)) {
		Engine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Joining: %s"), *Address));
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (ensure(PlayerController != nullptr)) {
		PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
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
