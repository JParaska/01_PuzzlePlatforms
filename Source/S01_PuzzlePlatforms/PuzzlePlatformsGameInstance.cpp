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
	UE_LOG(LogTemp, Warning, TEXT("Menu class: %s"), *MainMenuClass->GetName());
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get(NAME_None);
	if (OnlineSubsystem != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Online sub-system found: %s"), *OnlineSubsystem->GetSubsystemName().ToString());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Online sub-system"));
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
	UEngine* Engine = GetEngine();
	if (ensure(Engine != nullptr)) {
		Engine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Hosting"));
	}

	UWorld* World = GetWorld();
	if (ensure(World != nullptr)) {
		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}
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
