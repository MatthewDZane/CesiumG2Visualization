// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "G2SnapshotResponse.h"
#include "UE4Response.h"
#include "TimeStampIDPair.h"
#include "FlowInfo.h"
#include "ReztlyJson.h"

#include <queue>
#include "CoreMinimal.h"
#include "JsonObjectWrapper.h"
#include "NetboxRegionResponse.h"
#include "NetboxSiteResponse.h"
#include "NetboxDeviceResponse.h"
#include "NetboxLocationResponse.h"
#include "NetboxRackResponse.h"
#include "Avatars.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "JsonObjectConverter.h"

#include "JsonParser.generated.h"

/**
 * 
 */
UCLASS()
class CESIUMNETBOXVISUALIZATION_API UJsonParser : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UReztlyJson* StringToJson(FString JsonString);
	
	// G2 Snapshot Functions //
	/**
	 * Parses a G2 Bearer Token from a G2 Snapshot Response FString. Returns an
	 * empty FString if the Json String is not deserializable or does not have
	 * a "token" field.
	 */
	UFUNCTION(BlueprintCallable)
	static FString ParseBearerToken(FString JsonString);
	
	/**
	* Converts a G2 Snapshot Response FString to a FTimeStampIDPair struct
	*/
	UFUNCTION(BlueprintCallable)
	static TArray<FTimeStampIDPair> StringToAvailableSnapshots(
		FString JsonString
	);
	
	/**
	* Converts a G2 Snapshot Response FString to a FG2SnapshotResponse struct
	*/
	UFUNCTION(BlueprintCallable)
	static FG2SnapshotResponse StringToG2SnapshotResponse(FString JsonString);
	
	/**
	* Converts a FG2SnapshotResponse to a FJsonObjectWrapper
	*/
	UFUNCTION(BlueprintCallable)
	static FJsonObjectWrapper StructToG2SnapshotObject(
		FG2SnapshotResponse Response
	);

	/**
	* Converts a G2 Flow Info String to a FFlowInfo struct
	*/
	UFUNCTION(BlueprintCallable)
	static FFlowInfo StringToFlowInfo(FString JsonString);


	// UE4 Response Functions //
	/**
	* Converts a UE4 Response FString to a FUE4Response struct
	*/
	UFUNCTION(BlueprintCallable)
	static FUE4Response StringToUE4Response(FString JsonString);
	
	/**
	* Converts a FUE4Response to a FJsonObjectWrapper
	*/
	UFUNCTION(BlueprintCallable)
	static FJsonObjectWrapper StructToUE4ResponseObject(FUE4Response Response);


	// Netbox Region Response Functions //
	/**
	* Converts a Netbox Region Response FString to a FNetboxRegionResponse struct
	*/
	UFUNCTION(BlueprintCallable)
		static FNetboxRegionResponse StringToNetboxRegionResponse(
			FString JsonString
		);

	/**
	* Converts a FNetboxRegionResponse to a FJsonObjectWrapper
	*/
	UFUNCTION(BlueprintCallable)
		static FJsonObjectWrapper StructToNetboxRegionResponseObject(
			FNetboxRegionResponse Response);


	// Netbox Site Response Functions //
	/**
	* Converts a Netbox Site Response FString to a FNetboxSiteResponse struct
	*/
	UFUNCTION(BlueprintCallable)
	static FNetboxSiteResponse StringToNetboxSiteResponse(FString JsonString);
	
	/**
	* Converts a FNetboxSiteResponse to a FJsonObjectWrapper
	*/
	UFUNCTION(BlueprintCallable)
	static FJsonObjectWrapper StructToNetboxSiteResponseObject(
		FNetboxSiteResponse Response
	);


	// Netbox Location Response Functions //
	/**
	* Converts a Netbox Location Response FString to a FNetboxLocationResponse 
	* struct
	*/
	UFUNCTION(BlueprintCallable)
		static FNetboxLocationResponse StringToNetboxLocationResponse(
			FString JsonString
		);

	/**
	* Converts a FNetboxLocationResponse to a FJsonObjectWrapper
	*/
	UFUNCTION(BlueprintCallable)
		static FJsonObjectWrapper StructToNetboxLocationResponseObject(
			FNetboxLocationResponse Response
		);


	// Netbox Rack Response Functions //
	/**
	* Converts a Netbox Rack Response FString to a FNetboxRackResponse struct
	*/
	UFUNCTION(BlueprintCallable)
		static FNetboxRackResponse StringToNetboxRackResponse(
			FString JsonString
		);

	/**
	* Converts a FNetboxRackResponse to a FJsonObjectWrapper
	*/
	UFUNCTION(BlueprintCallable)
		static FJsonObjectWrapper StructToNetboxRackResponseObject(
			FNetboxRackResponse Response
		);


	// Netbox Device Response Functions //
	/**
	* Converts a Netbox Device Response FString to a FNetboxDeviceResponse 
	* struct
	*/
	UFUNCTION(BlueprintCallable)
		static FNetboxDeviceResponse StringToNetboxDeviceResponse(
			FString JsonString
		);

	/**
	* Converts a FNetboxDeviceResponse to a FJsonObjectWrapper
	*/
	UFUNCTION(BlueprintCallable)
		static FJsonObjectWrapper StructToNetboxDeviceResponseObject(
			FNetboxDeviceResponse Response
		);


	// Netbox Device Type Response Functions //
	/**
	* Converts a Netbox Device Response FString to a FNetboxDeviceResponse 
	* struct
	*/
	UFUNCTION(BlueprintCallable)
		static FNetboxDeviceTypeResponse StringToNetboxDeviceTypeResponse(
			FString JsonString
		);

	/**
	* Converts a FNetboxDeviceTypeResponse to a FJsonObjectWrapper
	*/
	UFUNCTION(BlueprintCallable)
		static FJsonObjectWrapper StructToNetboxDeviceTypeResponseObject(
			FNetboxDeviceTypeResponse Response
		);


	// Post Response Functions //
	/**
	* Converts a Netbox Post or Put Response FString to a TArray of
	* FG2SnapshotResponse struct
	*/
	UFUNCTION(BlueprintCallable)
	static TArray<FNetboxDevice> StringToDevices(FString JsonString);

	// Post Response Functions //
	/**
	* Converts a User Cloud request FString to a TArray of
	* FAvatarArrayStruct struct
	*/
	UFUNCTION(BlueprintCallable)
	static FAvatarArrayStruct StringToAvatars(FString JsonString);

	/**
	* Converts a FAvatarArrayStruct to a FJsonObjectWrapper
	*/
	UFUNCTION(BlueprintCallable)
	static FString StructToAvatarsJSON(FAvatarArrayStruct Response);

	/**
	* Converts a FResult to a FJsonObjectWrapper
	*/
	UFUNCTION(BlueprintCallable)
	static FJsonObjectWrapper StructToDeviceObject(FNetboxDevice Response);

	/**
	* Returns whether the field is in the JsonWrapper. The layers
	* of the path are separated by periods and array elements are specified
	* with square brackets surrounding the index.
	* Ex: "outside[0].middle.inner[3].field"
	*/
	UFUNCTION(BlueprintCallable)
	static bool FindFieldPath(
		FJsonObjectWrapper JsonWrapper,
		FString FieldPath
	);

	/**
	* Returns the String value of the field given in the Json String
	*/
	UFUNCTION(BlueprintCallable)
	static FString GetStringValue(FString JsonString, FString Field);

	/**
	* Returns the Float value of the field given in the Json String
	*/
	UFUNCTION(BlueprintCallable)
	static float GetFloatValue(FString JsonString, FString Field);
	
	/**
	* Returns the Float value of the field given in the Json String
	*/
	UFUNCTION(BlueprintCallable)
	static bool GetBoolValue(FString JsonString, FString Field);

private:
	
	/**
	* Check if the next field in the queue is in the JsonObject, if there
	* are more fields left then recursively check the next fields with
	* the previous field's value
	*/
	static bool FindField(TSharedPtr<FJsonObject> JsonObject,
						  std::queue<FString> Fields);
	
};

