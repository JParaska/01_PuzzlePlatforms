// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

class UMainMenu;

/**
 * 
 */
UCLASS()
class S01_PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

private:

	TSubclassOf<class UUserWidget> MainMenuClass;

	TSubclassOf<class UUserWidget> GameMenuClass;

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	UMainMenu* MainMenu;

	FString ServerName;

public:

	UPuzzlePlatformsGameInstance();

	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void LoadMenu();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void LoadGameMenu();

	UFUNCTION(Exec)
	virtual void Host(const FString ServerName) override;

	UFUNCTION()
	void OnSessionDestroyedCompleted(FName SessionName, bool Destroyed);

	UFUNCTION()
	void CreateSession();

	UFUNCTION()
	void OnSessionCreatedCompleted(FName SessionName, bool Created);

	UFUNCTION()
	void OnSessionFindCompleted(bool Success);

	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION(Exec)
	virtual void Join(const uint32 SessionIndex) override;

	UFUNCTION()
	virtual void LoadMainMenu() override;

	UFUNCTION()
	virtual void QuitGame() override;

	UFUNCTION()
	virtual void GetServerList() override;

	void StartSession();
};
