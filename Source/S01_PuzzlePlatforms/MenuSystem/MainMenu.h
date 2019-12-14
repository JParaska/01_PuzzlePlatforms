// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

class UButton;
class UWidgetSwitcher;
class UWidget;

/**
 * 
 */
UCLASS()
class S01_PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

/** Properties */
private:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelJoinMenuButton;

	IMenuInterface* MenuInterface;

/** Methods */
public:

	virtual bool Initialize();

	void SetMenuInterface(IMenuInterface* Interface);

	void Setup();

	void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();
	
};
