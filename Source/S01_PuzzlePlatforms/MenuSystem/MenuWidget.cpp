// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::Setup() {
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

void UMenuWidget::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld) {
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	SetGameOnlyInputMode();
}

void UMenuWidget::SetMenuInterface(IMenuInterface * Interface) {
	MenuInterface = Interface;
}

void UMenuWidget::SetGameOnlyInputMode() {
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
