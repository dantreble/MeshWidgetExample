// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MeshWidgetExample : ModuleRules
{
	public MeshWidgetExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "SlateCore", "Slate", "UMG", "AIModule" });
	}
}

