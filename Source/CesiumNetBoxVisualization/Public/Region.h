#pragma once

#include "NetboxRegionResponse.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Region.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class CESIUMNETBOXVISUALIZATION_API URegion : public UObject
{
	GENERATED_BODY()

public:
	URegion();
	~URegion();

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
		FString ParentName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Description;

	// Custom Fields
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* Logo;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString LogoUrl;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Latitude;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Longitude;

	UFUNCTION(BlueprintCallable)
		FRegionStruct ToStruct();
};