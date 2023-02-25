#pragma once

#include "NetboxDeviceResponse.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Site.h"
#include "Rack.h"
#include "DeviceType.h"

#include "Device.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CESIUMNETBOXVISUALIZATION_API UDevice : public UObject
{
	GENERATED_BODY()
	
public:
	UDevice();
	~UDevice();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int ID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Url;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Display;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString IP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int Position;

	// Custom Fields
	UPROPERTY(BlueprintReadWrite)
		FVector WorldLocationOffset;
	UPROPERTY(BlueprintReadWrite)
		FRotator WorldRotationOffset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Info;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MTU;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Primary;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USite* Site;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ULocation* Location;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		URack* Rack;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UDeviceType* DeviceType;

	UFUNCTION(BlueprintCallable)
		FNetboxDevice ToStruct();
};
