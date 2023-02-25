// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetboxSiteResponse.h"

#include "Region.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Site.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CESIUMNETBOXVISUALIZATION_API USite : public UObject
{
	GENERATED_BODY()

public:
	USite();
	USite(
		int IDIn,
		FString UrlIn,
		FString DisplayIn, 
		FString NameIn,
		FString SlugIn, 
		float LatitudeIn, 
		float LongitudeIn
	);
	~USite();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int ID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Url;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Display;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Slug;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString RegionName;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Latitude;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Longitude;

	UFUNCTION(BlueprintCallable)
		FSiteStruct ToStruct();
};
