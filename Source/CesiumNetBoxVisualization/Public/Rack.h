#pragma once

#include "NetboxRackResponse.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Site.h"
#include "Location.h"

#include "Rack.generated.h"

/**
 * 
 */
UCLASS()
class CESIUMNETBOXVISUALIZATION_API URack : public UObject
{
	GENERATED_BODY()
	
public:
	URack();
	~URack();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int ID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Url;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Display;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name;

	UPROPERTY(BlueprintReadWrite)
		FString FacilityID;
	UPROPERTY(BlueprintReadWrite)
		FString Status;
	UPROPERTY(BlueprintReadWrite)
		FString Role;
	UPROPERTY(BlueprintReadWrite)
		FString Serial;
	UPROPERTY(BlueprintReadWrite)
		FString AssetTag;
	UPROPERTY(BlueprintReadWrite)
		FString Type;
	UPROPERTY(BlueprintReadWrite)
		float Width;


	UPROPERTY(BlueprintReadWrite)
		int UHeight;
	UPROPERTY(BlueprintReadWrite)
		int OuterWidth;
	UPROPERTY(BlueprintReadWrite)
		int OuterDepth;
	UPROPERTY(BlueprintReadWrite)
		int OuterUnit;

	UPROPERTY(BlueprintReadWrite)
		FString Comments;

	UPROPERTY(BlueprintReadWrite)
		float RackLatitude;
	UPROPERTY(BlueprintReadWrite)
		float RackLongitude;
	UPROPERTY(BlueprintReadWrite)
		FVector WorldLocationOffset;
	UPROPERTY(BlueprintReadWrite)
		FRotator WorldRotationOffset;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USite* Site;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ULocation* Location;

	UFUNCTION(BlueprintCallable)
		FRackStruct ToStruct();
};
