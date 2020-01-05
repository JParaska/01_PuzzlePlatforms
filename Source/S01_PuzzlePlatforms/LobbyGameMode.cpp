// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

void ALobbyGameMode::PostLogin(APlayerController * NewPlayer) {
	Players++;
	UE_LOG(LogTemp, Warning, TEXT("Player logged in. # of players: %d"), Players);
}

void ALobbyGameMode::Logout(AController * Exiting) {
	Players--;
	UE_LOG(LogTemp, Warning, TEXT("Player logged out. # of players: %d"), Players);
}
