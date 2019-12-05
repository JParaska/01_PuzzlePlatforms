// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance() {
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuWidgetClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MenuWidgetClass.Class != nullptr) {
		MenuClass = MenuWidgetClass.Class;
	}
}

void UPuzzlePlatformsGameInstance::Init() {
	UE_LOG(LogTemp, Warning, TEXT("Menu class: %s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::Host() {
	UEngine* Engine = GetEngine();
	if (ensure(Engine != nullptr)) {
		Engine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Hosing"));
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
