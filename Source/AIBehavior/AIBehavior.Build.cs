// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AIBehavior : ModuleRules
{
	public AIBehavior(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "AIModule", "GameplayTasks","NavigationSystem" });
	}
}
