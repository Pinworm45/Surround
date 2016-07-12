// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Surround : ModuleRules
{
	public Surround(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
                "AIModule",
				"GameplayTasks",
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Slate",
				"SlateCore",
			}
		);
	}
}
