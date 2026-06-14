// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SimpleProject : ModuleRules
{
	public SimpleProject(ReadOnlyTargetRules Target) : base(Target)
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
			"SimpleProject",
			"SimpleProject/Variant_Platforming",
			"SimpleProject/Variant_Platforming/Animation",
			"SimpleProject/Variant_Combat",
			"SimpleProject/Variant_Combat/AI",
			"SimpleProject/Variant_Combat/Animation",
			"SimpleProject/Variant_Combat/Gameplay",
			"SimpleProject/Variant_Combat/Interfaces",
			"SimpleProject/Variant_Combat/UI",
			"SimpleProject/Variant_SideScrolling",
			"SimpleProject/Variant_SideScrolling/AI",
			"SimpleProject/Variant_SideScrolling/Gameplay",
			"SimpleProject/Variant_SideScrolling/Interfaces",
			"SimpleProject/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
