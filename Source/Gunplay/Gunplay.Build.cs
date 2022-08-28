// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gunplay : ModuleRules
{
	public Gunplay(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivatePCHHeaderFile = "Gunplay.h";
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Slate", "SlateCore" , "OnlineSubsystem", 
			"OnlineSubsystemUtils",  "Networking"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"OnlineSubsystem", "OnlineSubsystemUtils"
		});
	}
}