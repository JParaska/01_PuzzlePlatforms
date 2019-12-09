// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;

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
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

/** Methods */
public:

	virtual bool Initialize();

private:

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();
	
};
