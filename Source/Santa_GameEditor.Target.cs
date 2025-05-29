

using UnrealBuildTool;
using System.Collections.Generic;

public class Santa_GameEditorTarget : TargetRules
{
	public Santa_GameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Santa_Game" } );
	}
}
