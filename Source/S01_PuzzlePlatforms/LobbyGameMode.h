// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "S01_PuzzlePlatformsGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 *
 */
UCLASS()
class S01_PUZZLEPLATFORMS_API ALobbyGameMode : public AS01_PuzzlePlatformsGameMode {
	GENERATED_BODY()

/** Properties */
private:

	uint32 Players = 0;

	UPROPERTY()
	FTimerHandle StartGameTimer;

/** Methods */
public:

	virtual void PostLogin(APlayerController * NewPlayer) override;

	virtual void Logout(AController * Exiting) override;

private:

	void StartGame();
};
