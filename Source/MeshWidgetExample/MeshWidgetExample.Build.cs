// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MeshWidgetExample : ModuleRules
{
	public MeshWidgetExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "UMG" , "AIModule", "SlateCore" });
        
        if (Target.Version is { MajorVersion: >= 5, MinorVersion: >= 2 })
        {
	        PublicDependencyModuleNames.AddRange(
		        new[]
		        {
			        "XRBase",
		        }
	        );
        }
        else
        {
	        PublicDependencyModuleNames.AddRange(
		        new[]
		        {
			        "HeadMountedDisplay",
		        }
	        );
        }
    }
}
