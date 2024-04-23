// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MissionPossible : ModuleRules
{
	public MissionPossible(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
