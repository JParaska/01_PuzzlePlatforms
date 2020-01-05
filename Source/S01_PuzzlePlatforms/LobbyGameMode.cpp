// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "PuzzlePlatformsGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController * NewPlayer) {
	Super::PostLogin(NewPlayer);

	Players++;
	UE_LOG(LogTemp, Warning, TEXT("Player logged in. # of players: %d"), Players);
	if (Players >= 2) {
		GetWorldTimerManager().SetTimer(StartGameTimer, this, &ALobbyGameMode::StartGame, 10);
	}
}

void ALobbyGameMode::Logout(AController * Exiting) {
	Super::Logout(Exiting);
	Players--;
	UE_LOG(LogTemp, Warning, TEXT("Player logged out. # of players: %d"), Players);
}

void ALobbyGameMode::StartGame() {
	UWorld* World = GetWorld();
	if (World != nullptr) {
		auto GameInstance = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance());
		if (GameInstance != nullptr) {
			GameInstance->StartSession();
		}

		bUseSeamlessTravel = true;
		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}
}
