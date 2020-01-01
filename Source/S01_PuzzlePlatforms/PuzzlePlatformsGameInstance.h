// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "PuzzlePlatformsGameInstance.generated.h"

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

public:

	UPuzzlePlatformsGameInstance();

	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void LoadMenu();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void LoadGameMenu();

	UFUNCTION(Exec)
	virtual void Host() override;

	UFUNCTION()
	void OnSessionDestroyedCompleted(FName SessionName, bool Destroyed);

	UFUNCTION()
	void CreateSession();

	UFUNCTION()
	void OnSessionCreatedCompleted(FName SessionName, bool Created);

	UFUNCTION()
	void OnSessionFindCompleted(bool Success);

	UFUNCTION(Exec)
	virtual void Join(const FString& Address) override;

	UFUNCTION()
	virtual void LoadMainMenu() override;

	UFUNCTION()
	virtual void QuitGame() override;
};
