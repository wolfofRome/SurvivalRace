// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RaceForSurvival : ModuleRules
{
	public RaceForSurvival(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara", "MultiplayerSessions", "OnlineSubsystem", "OnlineSubsystemUtils", "OnlineSubsystemEOS" });

        PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags",  "GameplayTasks", "Slate", "SlateCore", "UMG" });
    }
}
