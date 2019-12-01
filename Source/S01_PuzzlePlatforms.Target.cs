// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class S01_PuzzlePlatformsTarget : TargetRules
{
	public S01_PuzzlePlatformsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("S01_PuzzlePlatforms");
	}
}
