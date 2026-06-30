// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TDMProject : ModuleRules
{
	public TDMProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TDMProject",
			"TDMProject/Variant_Platforming",
			"TDMProject/Variant_Platforming/Animation",
			"TDMProject/Variant_Combat",
			"TDMProject/Variant_Combat/AI",
			"TDMProject/Variant_Combat/Animation",
			"TDMProject/Variant_Combat/Gameplay",
			"TDMProject/Variant_Combat/Interfaces",
			"TDMProject/Variant_Combat/UI",
			"TDMProject/Variant_SideScrolling",
			"TDMProject/Variant_SideScrolling/AI",
			"TDMProject/Variant_SideScrolling/Gameplay",
			"TDMProject/Variant_SideScrolling/Interfaces",
			"TDMProject/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
