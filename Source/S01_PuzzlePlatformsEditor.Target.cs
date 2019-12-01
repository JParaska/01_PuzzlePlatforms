// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class S01_PuzzlePlatformsEditorTarget : TargetRules
{
	public S01_PuzzlePlatformsEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("S01_PuzzlePlatforms");
	}
}
