// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"
#include "Components/TextBlock.h"

void UServerRow::SetServerNameText(FText ServerNameText) {
	ServerName->SetText(ServerNameText);
}
