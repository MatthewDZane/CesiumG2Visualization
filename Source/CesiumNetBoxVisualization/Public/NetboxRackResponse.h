// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetboxResponse.h"

#include "NetboxRackResponse.generated.h"

USTRUCT(BlueprintType)
struct FCustomRackFields
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		float Rack_latitude;
	UPROPERTY(BlueprintReadWrite)
		float Rack_longitude;
	UPROPERTY(BlueprintReadWrite)
		FString Rack_world_location_offset;
	UPROPERTY(BlueprintReadWrite)
		FString Rack_world_rotation_offset;
};

USTRUCT(BlueprintType)
struct FRackSite
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
		int _depth;
};

USTRUCT(BlueprintType)
struct FRackLocation
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
		int _depth;
};

USTRUCT(BlueprintType)
struct FRackStruct
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
		FString Facility_id;
	UPROPERTY(BlueprintReadWrite)
		FRackSite Site;
	UPROPERTY(BlueprintReadWrite)
		FRackLocation Location;
	UPROPERTY(BlueprintReadWrite)
		FTenant Tenant;
	UPROPERTY(BlueprintReadWrite)
		FNetboxStatus Status;
	UPROPERTY(BlueprintReadWrite)
		FString Role;
	UPROPERTY(BlueprintReadWrite)
		FString Serial;
	UPROPERTY(BlueprintReadWrite)
		FString Asset_tag;
	UPROPERTY(BlueprintReadWrite)
		FNetboxType Type;
	UPROPERTY(BlueprintReadWrite)
		FNetboxWidth Width;
	UPROPERTY(BlueprintReadWrite)
		int U_height;
	UPROPERTY(BlueprintReadWrite)
		bool Desc_units;
	UPROPERTY(BlueprintReadWrite)
		int Outer_width;
	UPROPERTY(BlueprintReadWrite)
		int Outer_depth;
	UPROPERTY(BlueprintReadWrite)
		int Outer_unit;
	UPROPERTY(BlueprintReadWrite)
		FString Comments;
	UPROPERTY(BlueprintReadWrite)
		TArray<FTag> Tags;
	UPROPERTY(BlueprintReadWrite)
		FCustomRackFields Custom_fields;
	UPROPERTY(BlueprintReadWrite)
		FString Created;
	UPROPERTY(BlueprintReadWrite)
		FString Last_updated;
	UPROPERTY(BlueprintReadWrite)
		int device_count;
	UPROPERTY(BlueprintReadWrite)
		int powerfeed_count;
};

USTRUCT(BlueprintType)
struct FNetboxRackResponse
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
		TArray<FRackStruct> Results;
};