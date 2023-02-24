#pragma once

#include "NetboxResponse.h"

#include "NetboxSiteResponse.generated.h"


USTRUCT(BlueprintType)
struct FCustomSiteFields
{
	GENERATED_USTRUCT_BODY()
public:
};

USTRUCT(BlueprintType)
struct FGroup
{
	GENERATED_USTRUCT_BODY()
public:
};

USTRUCT(BlueprintType)
struct FSiteRegion
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FString Id;
	UPROPERTY(BlueprintReadWrite)
		FString Url;
	UPROPERTY(BlueprintReadWrite)
		FString Display;
	UPROPERTY(BlueprintReadWrite)
		FString Name;
	UPROPERTY(BlueprintReadWrite)
		FString Slug;
	UPROPERTY(BlueprintReadWrite)
		int _depth;
};

USTRUCT(BlueprintType)
struct FSiteStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		int Id;
	UPROPERTY(BlueprintReadWrite)
		FString Url;
	UPROPERTY(BlueprintReadWrite)
		FString Display;
	UPROPERTY(BlueprintReadWrite)
		FString Name;
	UPROPERTY(BlueprintReadWrite)
		FString Slug;
	UPROPERTY(BlueprintReadWrite)
		FNetboxStatus Status;
	UPROPERTY(BlueprintReadWrite)
		FSiteRegion Region;
	UPROPERTY(BlueprintReadWrite)
		FGroup Group;
	UPROPERTY(BlueprintReadWrite)
		FTenant Tenant;
	UPROPERTY(BlueprintReadWrite)
		FString Facility;
	UPROPERTY(BlueprintReadWrite)
		FString Time_zone;
	UPROPERTY(BlueprintReadWrite)
		FString Description;
	UPROPERTY(BlueprintReadWrite)
		FString Physical_address;
	UPROPERTY(BlueprintReadWrite)
		FString Shipping_address;
	UPROPERTY(BlueprintReadWrite)
		float Latitude;
	UPROPERTY(BlueprintReadWrite)
		float Longitude;
	UPROPERTY(BlueprintReadWrite)
		FString Comments;
	UPROPERTY(BlueprintReadWrite)
		TArray<FString> Asns;
	UPROPERTY(BlueprintReadWrite)
		TArray<FTag> Tags;
	UPROPERTY(BlueprintReadWrite)
		FCustomSiteFields Custom_fields;
	UPROPERTY(BlueprintReadWrite)
		FString Created;
	UPROPERTY(BlueprintReadWrite)
		FString Last_updated;
	UPROPERTY(BlueprintReadWrite)
		int Circuit_count;
	UPROPERTY(BlueprintReadWrite)
		int Device_count;
	UPROPERTY(BlueprintReadWrite)
		int Prefix_count;
	UPROPERTY(BlueprintReadWrite)
		int Rack_count;
	UPROPERTY(BlueprintReadWrite)
		int Virtualmachine_count;
	UPROPERTY(BlueprintReadWrite)
		int Vlan_count;
};


USTRUCT(BlueprintType)
struct FNetboxSiteResponse
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		int Count;
	UPROPERTY(BlueprintReadWrite)
		FString Next;
	UPROPERTY(BlueprintReadWrite)
		bool Previous;
	UPROPERTY(BlueprintReadWrite)
		TArray<FSiteStruct> Results;
};
