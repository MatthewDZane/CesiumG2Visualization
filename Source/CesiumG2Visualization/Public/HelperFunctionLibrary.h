// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/Texture2DDynamic.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HelperFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CESIUMG2VISUALIZATION_API UHelperFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		static int32 GetTexture2DDynamicWidth(UTexture2DDynamic* InTexture2DDynamicReference);
	UFUNCTION(BlueprintCallable)
		static int32 GetTexture2DDynamicHeight(UTexture2DDynamic* InTexture2DDynamicReference);
};
