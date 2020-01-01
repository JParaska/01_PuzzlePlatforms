// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer & ObjectInitializer) {
	static ConstructorHelpers::FClassFinder<UUserWidget> ServerRowWidgetClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (ServerRowWidgetClass.Class != nullptr) {
		ServerRowClass = ServerRowWidgetClass.Class;
	}
}

bool UMainMenu::Initialize() {
	bool bInitialized = Super::Initialize();
	if (!bInitialized) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(CancelJoinMenuButton != nullptr)) return false;
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(JoinServerButton != nullptr)) return false;
	JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);
	
	return true;
}

void UMainMenu::HostServer() {
	if (ensure(MenuInterface != nullptr)) {
		MenuInterface->Host();
	}
}

void UMainMenu::OpenJoinMenu() {
	if (ensure(MenuSwitcher != nullptr) && ensure(JoinMenu != nullptr)) {
		MenuSwitcher->SetActiveWidget(JoinMenu);
	}
}

void UMainMenu::OpenMainMenu() {
	if (ensure(MenuSwitcher != nullptr) && ensure(MainMenu != nullptr)) {
		MenuSwitcher->SetActiveWidget(MainMenu);
	}
}

void UMainMenu::JoinServer() {
	/*if (ensure(IPAddressTextBox != nullptr) && ensure(MenuInterface != nullptr)) {
		auto IPAddress = IPAddressTextBox->GetText();
		MenuInterface->Join(IPAddress.ToString());
	}*/
	if (ensure(ServerList != nullptr) && ensure(ServerRowClass != nullptr)) {
		UWorld* World = GetWorld();
		if (World != nullptr) {
			UServerRow* ServerRow = CreateWidget<UServerRow>(World, ServerRowClass);
			if (ServerRow != nullptr) {
				ServerList->AddChild(ServerRow);
			}
		}
	}
}

void UMainMenu::QuitGame() {
	if (ensure(MenuInterface != nullptr)) {
		MenuInterface->QuitGame();
	}
}
