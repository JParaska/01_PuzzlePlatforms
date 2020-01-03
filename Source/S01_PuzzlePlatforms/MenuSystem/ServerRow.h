// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

class UTextBlock;
class UMainMenu;
class UButton;

/**
 * 
 */
UCLASS()
class S01_PUZZLEPLATFORMS_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

/** Properties */
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
	UButton* RowButton;

	UPROPERTY()
	UMainMenu* ParentWidget;

	uint32 Index;

/** Functions */
public:

	void SetServerNameText(FText ServerNameText);

	void Setup(UMainMenu* Parent, uint32 Index);

private:

	UFUNCTION()
	void OnClicked();
};
