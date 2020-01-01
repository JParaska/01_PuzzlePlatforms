// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

class UTextBlock;

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

/** Functions */
public:

	void SetServerNameText(FText ServerNameText);
};
