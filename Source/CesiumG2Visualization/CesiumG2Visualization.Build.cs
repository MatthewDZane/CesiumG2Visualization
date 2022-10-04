// Some copyright should be here...

using UnrealBuildTool;

public class CesiumG2Visualization : ModuleRules
{
	public CesiumG2Visualization(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "Reztly",
				// ... add other public dependencies that you statically link with here ...
			}
			);

        if (Target.Platform != UnrealTargetPlatform.HoloLens)
        {
            //PublicDependencyModuleNames.AddRange(new string[] { "CesiumRuntime", "OnlineSubsystemRedpointEOS" });
            PublicDependencyModuleNames.AddRange(new string[] { "CesiumRuntime" });
        }

        PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
