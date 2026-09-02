// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Pink_Chocolate_V8 : ModuleRules
{
	public Pink_Chocolate_V8(ReadOnlyTargetRules Target) : base(Target)
	{
		CppStandard = CppStandardVersion.Cpp20;
		
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", 
			"Niagara",
			"AssetRegistry",
			"EnhancedInput",
			"GameplayTags",
			"Charon",
			"ItemDataRuntime",
			"GlobalEvents"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
