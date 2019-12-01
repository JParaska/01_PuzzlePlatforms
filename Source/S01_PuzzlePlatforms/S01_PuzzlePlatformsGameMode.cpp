// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "S01_PuzzlePlatformsGameMode.h"
#include "S01_PuzzlePlatformsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AS01_PuzzlePlatformsGameMode::AS01_PuzzlePlatformsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
