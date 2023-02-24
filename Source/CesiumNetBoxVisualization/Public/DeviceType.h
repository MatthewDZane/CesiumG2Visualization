#pragma once

#include "NetboxDeviceTypeResponse.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "DeviceType.generated.h"

/**
 *
 */
UCLASS()
class CESIUMNETBOXVISUALIZATION_API UDeviceType : public UObject
{
	GENERATED_BODY()

public:
	UDeviceType();
	~UDeviceType();

	UPROPERTY(BlueprintReadWrite)
		int Id;
	UPROPERTY(BlueprintReadWrite)
		FString Url;
	UPROPERTY(BlueprintReadWrite)
		FString Display;
	UPROPERTY(BlueprintReadWrite)
		FManufacturer Manufacturer;
	UPROPERTY(BlueprintReadWrite)
		FString Model;
	UPROPERTY(BlueprintReadWrite)
		FString Slug;
	UPROPERTY(BlueprintReadWrite)
		FString Part_number;
	UPROPERTY(BlueprintReadWrite)
		float U_height;
	UPROPERTY(BlueprintReadWrite)
		bool Is_full_depth;
	UPROPERTY(BlueprintReadWrite)
		FNetboxStatus Subdevice_role;
	UPROPERTY(BlueprintReadWrite)
		FNetboxStatus Airflow;
	UPROPERTY(BlueprintReadWrite)
		FString Front_image;
	UPROPERTY(BlueprintReadWrite)
		FString Rear_image;
	UPROPERTY(BlueprintReadWrite)
		FString Comments;
	UPROPERTY(BlueprintReadWrite)
		FCustomDeviceTypeFields Custom_fields;
	UPROPERTY(BlueprintReadWrite)
		FString Created;
	UPROPERTY(BlueprintReadWrite)
		FString Last_updated;
};
