// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "Engine/World.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance() {
	UE_LOG(LogTemp, Warning, TEXT("Constructor of game instance"));
}

void UPuzzlePlatformsGameInstance::Init() {
	UE_LOG(LogTemp, Warning, TEXT("Init function of game instance"));
}

void UPuzzlePlatformsGameInstance::Host() {
	UEngine* Engine = GetEngine();
	if (ensure(Engine != nullptr)) {
		Engine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Hosing"));
	}

	UWorld* World = GetWorld();
	if (ensure(World != nullptr)) {
		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}
}

void UPuzzlePlatformsGameInstance::Join(const FString & Address) {
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Joining: %s"), *Address));
}
