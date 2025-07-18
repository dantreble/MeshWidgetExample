// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MeshWidgetExampleEditorTarget : TargetRules 
{
	public MeshWidgetExampleEditorTarget(TargetInfo Target) : base(Target) 
	{ 
		Type = TargetType.Editor;
		//DefaultBuildSettings = BuildSettingsVersion.V2;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		ExtraModuleNames.Add("MeshWidgetExample");
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		CppStandard = CppStandardVersion.Cpp20; 
	} 
}
