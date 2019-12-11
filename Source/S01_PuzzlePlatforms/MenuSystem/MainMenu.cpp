// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Engine/World.h"

bool UMainMenu::Initialize() {
	bool bInitialized = Super::Initialize();
	if (!bInitialized) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	
	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface * Interface) {
	MenuInterface = Interface;
}

void UMainMenu::Setup() {
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (World != nullptr) {
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (ensure(PlayerController != nullptr)) {
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(this->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld) {
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	UWorld* World = GetWorld();
	if (World != nullptr) {
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (ensure(PlayerController != nullptr)) {
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = false;
		}
	}
}

void UMainMenu::HostServer() {
	UE_LOG(LogTemp, Warning, TEXT("Host button clicked"));
	if (ensure(MenuInterface != nullptr)) {
		MenuInterface->Host();
	}
}

void UMainMenu::JoinServer() {
	UE_LOG(LogTemp, Warning, TEXT("Join button clicked"));
}
