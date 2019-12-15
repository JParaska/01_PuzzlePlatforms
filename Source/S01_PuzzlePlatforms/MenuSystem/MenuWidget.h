// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class S01_PUZZLEPLATFORMS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

/** Properties */
protected:
	IMenuInterface* MenuInterface;
	
/** Methods */
public:

	void Setup();

	void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	void SetMenuInterface(IMenuInterface* Interface);

protected:

	void SetGameOnlyInputMode();
};
