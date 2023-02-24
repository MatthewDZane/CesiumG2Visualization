// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Http.h"
#include "JsonParser.h"

#include "ReztlyFStringResponse.h"
#include "ReztlyImageResponse.h"
#include "G2Node.h"
#include "Site.h"
#include "NetboxLocationResponse.h"
#include "NetboxRackResponse.h"

#include "ReztlyLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CESIUMNETBOXVISUALIZATION_API UReztly : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static const int TBD_DEVICE_TYPE_ID = 85;
	static const int TBD_DEVICE_ROLE = 29;
	
	UFUNCTION(BlueprintCallable)
		static void RequestBearerToken(
			FString G2Username, 
			FString G2Password,
			FString G2APIUrl,
			FStringResponseDelegate OnBearerTokenResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestSnapshotRange(
			FString G2APIUrl, 
			FString G2BearerToken,
			FStringResponseDelegate OnSnapshotRangeResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestSnapshot(
			int SnapshotID,
			FString G2APIUrl,
			FString G2BearerToken,
			FStringResponseDelegate OnSnapshotResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestUE4NautilusData(
			FString UE4NautilusDataUtilsUrl, 
			FStringResponseDelegate OnUE4NautliusDataResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxGet(
			FString NetboxUrl, 
			FString NetboxToken,
			FStringResponseDelegate OnNetboxRegionsGetResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxRegionsGet(
			FString NetboxUrl, 
			FString NetboxToken,
			FStringResponseDelegate OnNetboxRegionsGetResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxRegionPatch(
			FRegionStruct Region, 
			FString NetboxUrl, 
			FString NetboxToken,
			FStringResponseDelegate OnNetboxPatchResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxSitesGet(
			FString NetboxUrl,
			FString NetboxToken,
			FStringResponseDelegate OnNetboxSitesGetResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxSitePatch(
			FSiteStruct Site, 
			FString NetboxUrl, 
			FString NetboxToken,
			FStringResponseDelegate OnNetboxSitePatchResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxLocationsGet(
			FString NetboxUrl,
			FString NetboxToken,
			FStringResponseDelegate OnNetboxLocationsGetResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxLocationsGetBySite(
			FSiteStruct Site, 
			FString NetboxUrl, 
			FString NetboxToken,
			FStringResponseDelegate OnNetboxLocationsGetBySiteResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxLocationPatch(
			FLocationStruct Location, 
			FString NetboxUrl, 
			FString NetboxToken,
			FStringResponseDelegate OnNetboxLocationPatchResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxRacksGet(
			FString NetboxUrl, 
			FString NetboxToken,
			FStringResponseDelegate OnNetboxRacksGetResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxRacksGetBySite(
			FSiteStruct Site, 
			FString NetboxUrl, 
			FString NetboxToken,
			FStringResponseDelegate OnNetboxRacksGetBySiteResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxRacksGetByLocation(
			FLocationStruct Location,
			FString NetboxUrl, 
			FString NetboxToken,
			FStringResponseDelegate OnNetboxRacksGetByLocationResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxRackPatch(
			FRackStruct Rack, 
			FString NetboxUrl, 
			FString NetboxToken,
			FStringResponseDelegate OnNetboxRackPatchResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxDeviceTypesGet(
			FString NetboxUrl, 
			FString NetboxToken,
			FStringResponseDelegate OnNetboxDevicesTypeGetResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxDevicesGet(
			FString NetboxUrl, 
			FString NetboxToken,
			FStringResponseDelegate OnNetboxDeviceGetResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxDevicesPost(
			TArray<FNetboxDevice> Devices, 
			FString NetboxUrl,
			FString NetboxToken, 
			FStringResponseDelegate OnNetboxPostResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxDevicesPatch(
			TArray<FNetboxDevice> Devices,
			FString NetboxUrl, 
			FString NetboxToken,
			FStringResponseDelegate OnNetboxPatchResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestImageGet(
			FString ImageUrl, 
			FImageResponseDelegate OnImageGetResponse
		);   
};
