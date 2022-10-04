// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperFunctionLibrary.h"

int32 UHelperFunctionLibrary::GetTexture2DDynamicWidth(UTexture2DDynamic* InTexture2DDynamicReference)
{
	if (!InTexture2DDynamicReference)
	{
		return -1;
	}

	return InTexture2DDynamicReference->SizeX;
}

int32 UHelperFunctionLibrary::GetTexture2DDynamicHeight(UTexture2DDynamic* InTexture2DDynamicReference)
{
	if (!InTexture2DDynamicReference)
	{
		return -1;
	}

	return InTexture2DDynamicReference->SizeY;
}