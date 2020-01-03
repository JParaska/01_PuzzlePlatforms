// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"
#include "Components/TextBlock.h"
#include "MainMenu.h"
#include "Components/Button.h"

void UServerRow::SetServerNameText(FText ServerNameText) {
	ServerName->SetText(ServerNameText);
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
