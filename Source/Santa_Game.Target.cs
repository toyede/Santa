

using UnrealBuildTool;
using System.Collections.Generic;

public class Santa_GameTarget : TargetRules
{
	public Santa_GameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Santa_Game" } );
	}
}
