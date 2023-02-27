// Fill out your copyright notice in the Description page of Project Settings.


#include "CesiumNetBoxVisualizationRequestLibrary.h"

#include "ReztlyFunctionLibrary.h"

void UCesiumNetBoxVisualizationRequestLibrary::RequestBearerToken(
	FString G2Username, 
	FString G2Password, 
	FString G2APIUrl,
    FResponseDelegate OnBearerTokenResponseDelegate
) {
	FString Url = G2APIUrl + "/api/auth/login";

	TSharedPtr<FJsonObject> RequestBody = MakeShareable(new FJsonObject);
	RequestBody->SetStringField("username", G2Username);
	RequestBody->SetStringField("password", G2Password);

	FString RequestBodyString;
	TSharedRef<TJsonWriter<>> Writer =
		TJsonWriterFactory<>::Create(&RequestBodyString);
	FJsonSerializer::Serialize(RequestBody.ToSharedRef(), Writer);

	UReztlyFunctionLibrary::MakeRequest(
		Url, 
		EReztlyVerb::POST,
		TMap<FString, FString>(),
		RequestBodyString, 
		OnBearerTokenResponseDelegate
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestSnapshotRange(
	FString G2APIUrl, 
	FString G2BearerToken,
	FResponseDelegate OnSnapshotRangeResponse
) {
	FString Url = G2APIUrl + "api/tsrange/-1/0";

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Bearer " + G2BearerToken);

	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::GET,
		Headers,
		"",
		OnSnapshotRangeResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestSnapshot(
	int SnapshotID, 
	FString G2APIUrl, 
	FString G2BearerToken,
	FResponseDelegate OnSnapshotResponse
) {
	FString Url = G2APIUrl + "api/snapshot?id=" + FString::FromInt(SnapshotID);

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Bearer " + G2BearerToken);

	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::GET,
		Headers,
		"",
		OnSnapshotResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestUE4NautilusData(
	FString UE4NautilusDataUtilsUrl, 
	FResponseDelegate OnUE4NautilusDataResponse
) {
	UReztlyFunctionLibrary::MakeRequest(
		UE4NautilusDataUtilsUrl,
		EReztlyVerb::GET,
		TMap<FString, FString>(),
		"",
		OnUE4NautilusDataResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxGet(
	FString NetboxUrl, 
	FString NetboxToken,
	FResponseDelegate OnNetboxResponse
) {
	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	UReztlyFunctionLibrary::MakeRequest(
		NetboxUrl,
		EReztlyVerb::GET,
		Headers,
		"",
		OnNetboxResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxRegionsGet(
	FString NetboxUrl, 
	FString NetboxToken,
	FResponseDelegate OnNetboxRegionsResponse
) {
	FString Url = NetboxUrl + "/dcim/regions/?limit=0&offset=0";

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::GET,
		Headers,
		"",
		OnNetboxRegionsResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxRegionPatch(
	FRegionStruct Region, 
	FString NetboxUrl, 
	FString NetboxToken,
	FResponseDelegate OnNetboxRegionPatchResponse
) {
	FString Url = NetboxUrl + "/dcim/regions/";

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	FString RequestBody = 
		"[{\"id\":" + FString::FromInt(Region.Id) +
		",\"custom_fields\":{" +
		"\"region_latitude\":\"" + Region.Custom_fields.Region_latitude +
		"\",\"region_longitude\":\"" + 
		Region.Custom_fields.Region_longitude + "\"}}]";

	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::PATCH,
		Headers,
		RequestBody,
		OnNetboxRegionPatchResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxSitesGet(
	FString NetboxUrl, FString NetboxToken,
	FResponseDelegate OnNetboxSitesGetResponse)
{
	FString Url = NetboxUrl + "/dcim/sites/?limit=0&offset=0";

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::GET,
		Headers,
		"",
		OnNetboxSitesGetResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxSitePatch(
	FSiteStruct Site, 
	FString NetboxUrl, 
	FString NetboxToken,
	FResponseDelegate OnNetboxSitePatchResponse
) {
	FString Url = NetboxUrl + "/dcim/sites/";

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	FString RequestBody = 
		"[{\"id\":" + FString::FromInt(Site.Id) + ",\"latitude\":" +
		FString::SanitizeFloat(Site.Latitude) + ",\"longitude\":" +
		FString::SanitizeFloat(Site.Longitude) + "}]";

	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::PATCH,
		Headers,
		RequestBody,
		OnNetboxSitePatchResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxLocationsGet(
	FString NetboxUrl, 
	FString NetboxToken,
	FResponseDelegate OnNetboxLocationsGetResponse
) {
	FString Url = NetboxUrl + "/dcim/locations/?limit=0&offset=0";

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::GET,
		Headers,
		"",
		OnNetboxLocationsGetResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxLocationsGetBySite(
	FSiteStruct Site, 
	FString NetboxUrl, 
	FString NetboxToken,
	FResponseDelegate OnNetboxLocationsGetBySiteResponse
) {
	FString Url = 
		NetboxUrl + "/dcim/locations/?limit=0&offset=0&site=" +	Site.Slug;

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::GET,
		Headers,
		"",
		OnNetboxLocationsGetBySiteResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxLocationPatch(
	FLocationStruct Location, 
	FString NetboxUrl, 
	FString NetboxToken,
	FResponseDelegate OnNetboxLocationPatchResponse
) {
	FString Url = NetboxUrl + "/dcim/locations/";

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	FString RequestBody = 
		"[{\"id\":" + FString::FromInt(Location.Id) +
		",\"custom_fields\":{" +
		"\"location_world_location_offset\":\"" + 
		Location.Custom_fields.Location_world_location_offset +
		"\",\"location_world_rotation_offset\":\"" + 
		Location.Custom_fields.Location_world_rotation_offset + "\"}}]";

	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::PATCH,
		Headers,
		RequestBody,
		OnNetboxLocationPatchResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxRacksGet(
	FString NetboxUrl, FString NetboxToken,
	FResponseDelegate OnNetboxRacksGetResponse)
{
	FString Url = NetboxUrl + "/dcim/racks/?limit=0&offset=0";

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::GET,
		Headers,
		"",
		OnNetboxRacksGetResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxRacksGetBySite(
	FSiteStruct Site, 
	FString NetboxUrl, 
	FString NetboxToken,
	FResponseDelegate OnNetboxRacksGetResponse
) {
	FString Url = NetboxUrl + "/dcim/racks/?limit=0&offset=0&site=" + Site.Slug;

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::GET,
		Headers,
		"",
		OnNetboxRacksGetResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxRacksGetByLocation(
	FLocationStruct Location, 
	FString NetboxUrl, 
	FString NetboxToken,
	FResponseDelegate OnNetboxRacksGetResponse
) {
	FString Url = NetboxUrl + "/dcim/racks/?limit=0&offset=0&location=" + Location.Slug;

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::PATCH,
		Headers,
		"",
		OnNetboxRacksGetResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxRackPatch(
	FRackStruct Rack, 
	FString NetboxUrl, 
	FString NetboxToken,
	FResponseDelegate OnNetboxRackPatchResponse
) {
	FString Url = NetboxUrl + "/dcim/racks/";

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	FString RequestBody = 
		"[{\"id\":" + FString::FromInt(Rack.Id) +
		",\"custom_fields\":{" +
		"\"rack_latitude\":" + 
		FString::SanitizeFloat(Rack.Custom_fields.Rack_latitude) +
		"\"rack_longitude\":" + 
		FString::SanitizeFloat(Rack.Custom_fields.Rack_longitude) +
		"\"rack_world_location_offset\":\"" + 
		Rack.Custom_fields.Rack_world_location_offset +
		"\",\"rack_world_rotation_offset\":\"" + 
		Rack.Custom_fields.Rack_world_rotation_offset + "\"}}]";


	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::PATCH,
		Headers,
		RequestBody,
		OnNetboxRackPatchResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxDeviceTypesGet(
	FString NetboxUrl, 
	FString NetboxToken,
	FResponseDelegate OnNetboxDataResponse
) {
	FString Url = NetboxUrl + "/dcim/device-types/?limit=0&offset=0";

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::GET,
		Headers,
		"",
		OnNetboxDataResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxDevicesGet(
	FString NetboxUrl, 
	FString NetboxToken,
	FResponseDelegate OnNetboxDataResponse
) {
	FString Url = NetboxUrl + "/dcim/devices/?limit=0&offset=0";

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::GET,
		Headers,
		"",
		OnNetboxDataResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxDevicesPost(
	TArray<FNetboxDevice> Devices, 
	FString NetboxUrl, 
	FString NetboxToken, 
	FResponseDelegate OnNetboxPostResponse
) {
	FString Url = NetboxUrl + "/dcim/devices/";

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	FString RequestBody = "[";
	for (int i = 0; i < Devices.Num(); i++) {
		FNetboxDevice Device = Devices[i];
		FString NodeBodyString =
			"{\"name\":\"" + Device.Name +
			"\",\"device_type\":" + FString::FromInt(TBD_DEVICE_TYPE_ID) +
			",\"device_role\":" + FString::FromInt(TBD_DEVICE_ROLE) +
			",\"site\":" + FString::FromInt(Device.Site.Id) +
			",\"custom_fields\":{" +
			"\"info\":\"" + Device.Custom_fields.Info +
			"\",\"mtu\":" + FString::FromInt(Device.Custom_fields.Mtu) +
			",\"primary\":" + 
			(Device.Custom_fields.Primary ? "true" : "false") +
			"}}";

		RequestBody += NodeBodyString;

		if (i < Devices.Num() - 1)
		{
			RequestBody += ",";
		}
	}
	RequestBody += "]";


	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::POST,
		Headers,
		RequestBody,
		OnNetboxPostResponse
	);
}

void UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxDevicesPatch(
	TArray<FNetboxDevice> Devices, FString NetboxUrl, FString NetboxToken,
	FResponseDelegate OnNetboxPatchResponse)
{
	FString Url = NetboxUrl + "/dcim/devices/";

	TMap<FString, FString> Headers;
	Headers.Add("Content-Type", "application/json");
	Headers.Add("Authorization", "Token " + NetboxToken);

	FString RequestBody = "[";
	for (int i = 0; i < Devices.Num(); i++) {
		FNetboxDevice Device = Devices[i];
		FString DeviceBodyString =
			"{\"id\":" + FString::FromInt(Device.Id) +
			",\"name\":\"" + Device.Name +
			"\",\"Site_id\":" + FString::FromInt(Device.Site.Id) +
			",\"Location_id\":" + FString::FromInt(Device.Location.Id) +
			",\"Rack_id\":" + FString::FromInt(Device.Rack.Id) +
			",\"custom_fields\":{" +
			"\"device_world_location_offset\":\"" + 
			Device.Custom_fields.Device_world_location_offset +
			"\",\"device_world_rotation_offset\":\"" + 
			Device.Custom_fields.Device_world_rotation_offset +
			"\",\"info\":\"" + Device.Custom_fields.Info +
			"\",\"mtu\":" + FString::FromInt(Device.Custom_fields.Mtu) +
			",\"primary\":" + 
			(Device.Custom_fields.Primary ? "true" : "false") +
			"}}";

		RequestBody += DeviceBodyString;

		if (i < Devices.Num() - 1) {
			RequestBody += ",";
		}
	}
	RequestBody += "]";


	UReztlyFunctionLibrary::MakeRequest(
		Url,
		EReztlyVerb::PATCH,
		Headers,
		RequestBody,
		OnNetboxPatchResponse
	);
}
