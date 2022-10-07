// Copyright Epic Games, Inc. All Rights Reserved.

#include "CesiumNetBoxVisualizationBPLibrary.h"
#include "CesiumNetBoxVisualization.h"

UCesiumNetBoxVisualizationBPLibrary::UCesiumNetBoxVisualizationBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

int32 UCesiumNetBoxVisualizationBPLibrary::GetTexture2DDynamicWidth(UTexture2DDynamic* InTexture2DDynamicReference)
{
	if (!InTexture2DDynamicReference)
	{
		return -1;
	}

	return InTexture2DDynamicReference->SizeX;
}

int32 UCesiumNetBoxVisualizationBPLibrary::GetTexture2DDynamicHeight(UTexture2DDynamic* InTexture2DDynamicReference)
{
	if (!InTexture2DDynamicReference)
	{
		return -1;
	}

	return InTexture2DDynamicReference->SizeY;
}
