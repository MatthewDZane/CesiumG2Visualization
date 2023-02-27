// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Http.h"

#include "ReztlyResponse.h"
#include "G2Node.h"
#include "Site.h"
#include "NetboxLocationResponse.h"
#include "NetboxRackResponse.h"

#include "CesiumNetBoxVisualizationRequestLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CESIUMNETBOXVISUALIZATION_API UCesiumNetBoxVisualizationRequestLibrary :
	public UBlueprintFunctionLibrary
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
			FResponseDelegate OnBearerTokenResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestSnapshotRange(
			FString G2APIUrl, 
			FString G2BearerToken,
			FResponseDelegate OnSnapshotRangeResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestSnapshot(
			int SnapshotID,
			FString G2APIUrl,
			FString G2BearerToken,
			FResponseDelegate OnSnapshotResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestUE4NautilusData(
			FString UE4NautilusDataUtilsUrl, 
			FResponseDelegate OnUE4NautliusDataResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxGet(
			FString NetboxUrl, 
			FString NetboxToken,
			FResponseDelegate OnNetboxRegionsGetResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxRegionsGet(
			FString NetboxUrl, 
			FString NetboxToken,
			FResponseDelegate OnNetboxRegionsGetResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxRegionPatch(
			FRegionStruct Region, 
			FString NetboxUrl, 
			FString NetboxToken,
			FResponseDelegate OnNetboxPatchResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxSitesGet(
			FString NetboxUrl,
			FString NetboxToken,
			FResponseDelegate OnNetboxSitesGetResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxSitePatch(
			FSiteStruct Site, 
			FString NetboxUrl, 
			FString NetboxToken,
			FResponseDelegate OnNetboxSitePatchResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxLocationsGet(
			FString NetboxUrl,
			FString NetboxToken,
			FResponseDelegate OnNetboxLocationsGetResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxLocationsGetBySite(
			FSiteStruct Site, 
			FString NetboxUrl, 
			FString NetboxToken,
			FResponseDelegate OnNetboxLocationsGetBySiteResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxLocationPatch(
			FLocationStruct Location, 
			FString NetboxUrl, 
			FString NetboxToken,
			FResponseDelegate OnNetboxLocationPatchResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxRacksGet(
			FString NetboxUrl, 
			FString NetboxToken,
			FResponseDelegate OnNetboxRacksGetResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxRacksGetBySite(
			FSiteStruct Site, 
			FString NetboxUrl, 
			FString NetboxToken,
			FResponseDelegate OnNetboxRacksGetBySiteResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxRacksGetByLocation(
			FLocationStruct Location,
			FString NetboxUrl, 
			FString NetboxToken,
			FResponseDelegate OnNetboxRacksGetByLocationResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxRackPatch(
			FRackStruct Rack, 
			FString NetboxUrl, 
			FString NetboxToken,
			FResponseDelegate OnNetboxRackPatchResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxDeviceTypesGet(
			FString NetboxUrl, 
			FString NetboxToken,
			FResponseDelegate OnNetboxDevicesTypeGetResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxDevicesGet(
			FString NetboxUrl, 
			FString NetboxToken,
			FResponseDelegate OnNetboxDeviceGetResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxDevicesPost(
			TArray<FNetboxDevice> Devices, 
			FString NetboxUrl,
			FString NetboxToken, 
			FResponseDelegate OnNetboxPostResponse
		);

	UFUNCTION(BlueprintCallable)
		static void RequestNetboxDevicesPatch(
			TArray<FNetboxDevice> Devices,
			FString NetboxUrl, 
			FString NetboxToken,
			FResponseDelegate OnNetboxPatchResponse
		);
 
};
