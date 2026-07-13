// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Pink_Chocolate_V8EditorTarget : TargetRules
{
	public Pink_Chocolate_V8EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V7;

		ExtraModuleNames.AddRange( new string[] { "Pink_Chocolate_V8" } );
	}
}
