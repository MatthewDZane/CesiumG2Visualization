// Copyright Epic Games, Inc. All Rights Reserved.

#include "CesiumG2Visualization.h"

#define LOCTEXT_NAMESPACE "FCesiumG2VisualizationModule"

void FCesiumG2VisualizationModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FCesiumG2VisualizationModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCesiumG2VisualizationModule, CesiumG2Visualization)