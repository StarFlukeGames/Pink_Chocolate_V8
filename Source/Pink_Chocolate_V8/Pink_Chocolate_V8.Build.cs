// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Pink_Chocolate_V8 : ModuleRules
{
	public Pink_Chocolate_V8(ReadOnlyTargetRules Target) : base(Target)
	{
		CppStandard = CppStandardVersion.Cpp23;
		
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore", 
			"EnhancedInput",
			"GameplayTags",
			"GameplayAbilities",
			"GameplayTasks",
			"CommonUI",
			"CommonInput",
			"DeveloperSettings",
			"Niagara",
			"AssetRegistry",
			"NinjaInput",
			"NinjaGAS",
			"GlobalEvents",
			"Attributes",
			"SaveExtension",
			"ActionsExtension",
			"FactionsExtension",
			"StructUtils",
			
			// Generic Game System Sub-Modules
			"GenericGameSystem",
			"GenericSettingsSystem",
			"GenericEffectsSystem",
			"GenericUISystem",

			// Ecosystem Plugins
			"Glyphic",
			"NinjaGAS",
			"ItemDataRuntime"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
