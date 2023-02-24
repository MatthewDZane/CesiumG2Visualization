#pragma once

#include "NetboxLocationResponse.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Site.h"

#include "Location.generated.h"

class URack;

/**
 * 
 */
UCLASS()
class CESIUMNETBOXVISUALIZATION_API ULocation : public UObject
{
	GENERATED_BODY()
	
public:
	ULocation();
	~ULocation();

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

	UPROPERTY(BlueprintReadWrite)
		FVector LocationWorldLocationOffset;
	UPROPERTY(BlueprintReadWrite)
		FRotator LocationWorldRotationOffset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USite* Site;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ULocation* Parent;

	UFUNCTION(BlueprintCallable)
		FLocationStruct ToStruct();
};
