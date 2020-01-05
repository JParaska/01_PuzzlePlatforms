// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "Engine/World.h"

void ALobbyGameMode::PostLogin(APlayerController * NewPlayer) {
	Super::PostLogin(NewPlayer);

	Players++;
	UE_LOG(LogTemp, Warning, TEXT("Player logged in. # of players: %d"), Players);
	if (Players >= 3) {
		UWorld* World = GetWorld();
		if (World != nullptr) {
			bUseSeamlessTravel = true;
			World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
		}
	}
}

void ALobbyGameMode::Logout(AController * Exiting) {
	Super::Logout(Exiting);
	Players--;
	UE_LOG(LogTemp, Warning, TEXT("Player logged out. # of players: %d"), Players);
}
