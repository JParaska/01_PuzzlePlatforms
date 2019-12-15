// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenu.h"
#include "Components/Button.h"

bool UGameMenu::Initialize() {
	bool bInitialized = Super::Initialize();
	if (!bInitialized) return false;

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UGameMenu::CloseGameMenu);

	if (!ensure(MenuButton != nullptr)) return false;
	MenuButton->OnClicked.AddDynamic(this, &UGameMenu::BackToMainMenu);

	return true;
}

void UGameMenu::CloseGameMenu() {
	this->RemoveFromViewport();

	SetGameOnlyInputMode();
}

void UGameMenu::BackToMainMenu() {
	if (ensure(MenuInterface != nullptr)) {
		CloseGameMenu();
		MenuInterface->LoadMainMenu();
	}
}
