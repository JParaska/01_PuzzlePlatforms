// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "GameMenu.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class S01_PUZZLEPLATFORMS_API UGameMenu : public UMenuWidget
{
	GENERATED_BODY()

/** Properties */
private:
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MenuButton;

/** Methods */
public:

	virtual bool Initialize();

	UFUNCTION()
	void CloseGameMenu();

	UFUNCTION()
	void BackToMainMenu();
	
};
