// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"
#include "Components/TextBlock.h"
#include "MainMenu.h"
#include "Components/Button.h"

void UServerRow::SetServerNameText(const FText ServerNameText) {
	ServerName->SetText(ServerNameText);
}

void UServerRow::SetHostUserNameText(const FText HostUserNameText) {
	HostUserName->SetText(HostUserNameText);
}

void UServerRow::SetPlayersNumberText(const uint16 CurrentPlayers, const uint16 MaxPlayers) {
	Players->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), CurrentPlayers, MaxPlayers)));
}

void UServerRow::Setup(UMainMenu * Parent, uint32 Index) {
	ParentWidget = Parent;
	this->Index = Index;
	if (ensure(RowButton != nullptr)) {
		RowButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
	}
}

void UServerRow::OnClicked() {
	if (ParentWidget != nullptr) {
		ParentWidget->SelectIndex(Index);
	}
}
