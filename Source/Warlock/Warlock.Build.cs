// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Warlock : ModuleRules
{
	public Warlock(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
