// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetboxResponse.h"
#include "NetboxDeviceTypeResponse.h"

#include "NetboxDeviceResponse.generated.h"

USTRUCT(BlueprintType)
struct FDeviceRole
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
};

USTRUCT(BlueprintType)
struct FPlatform
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
};

USTRUCT(BlueprintType)
struct FDeviceSite
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
};

USTRUCT(BlueprintType)
struct FDeviceLocation
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
struct FDeviceRack
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
		int _depth;
};

USTRUCT(BlueprintType)
struct FFace
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FString Value;
	UPROPERTY(BlueprintReadWrite)
		FString Label;
};


USTRUCT(BlueprintType)
struct FDeviceBay
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

};

USTRUCT(BlueprintType)
struct FParentDevice
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
		FDeviceBay Device_bay;
};

USTRUCT(BlueprintType)
struct FPrimaryIp
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
		FString Family;
	UPROPERTY(BlueprintReadWrite)
		FString Address;  
};

USTRUCT(BlueprintType)
struct FCluster
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
};

USTRUCT(BlueprintType)
struct FVirtualChassis
{
	GENERATED_USTRUCT_BODY()
public:
};

USTRUCT(BlueprintType)
struct FLocalContextData
{
	GENERATED_USTRUCT_BODY()
public:
};

USTRUCT(BlueprintType)
struct FCustomDeviceFields
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FString	Device_world_location_offset;
	UPROPERTY(BlueprintReadWrite)
		FString	Device_world_rotation_offset;
	UPROPERTY(BlueprintReadWrite)
		FString Info;
	UPROPERTY(BlueprintReadWrite)
		int Mtu;
	UPROPERTY(BlueprintReadWrite)
		bool Primary;
	UPROPERTY(BlueprintReadWrite)
		FString Elevation;
	UPROPERTY(BlueprintReadWrite)
		FString Heading;
	UPROPERTY(BlueprintReadWrite)
		FString Pitch;
	UPROPERTY(BlueprintReadWrite)
		FString Roll;
};

USTRUCT(BlueprintType)
struct FReztlyConfigContext
{
	GENERATED_USTRUCT_BODY()
public:
};

USTRUCT(BlueprintType)
struct FNetboxDevice
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
		FNetboxDeviceType Device_Type;
	UPROPERTY(BlueprintReadWrite)
		FDeviceRole Device_Role;
	UPROPERTY(BlueprintReadWrite)
		FTenant Tenant;
	UPROPERTY(BlueprintReadWrite)
		FPlatform Platform;
	UPROPERTY(BlueprintReadWrite)
		FString Serial;
	UPROPERTY(BlueprintReadWrite)
		FString Asset_Tag;
	UPROPERTY(BlueprintReadWrite)
		FDeviceSite Site;
	UPROPERTY(BlueprintReadWrite)
		FDeviceLocation Location;
	UPROPERTY(BlueprintReadWrite)
		FDeviceRack Rack;
	UPROPERTY(BlueprintReadWrite)
		int Position;
	UPROPERTY(BlueprintReadWrite)
		FFace Face;
	UPROPERTY(BlueprintReadWrite)
		FParentDevice Parent_device;
	UPROPERTY(BlueprintReadWrite)
		FNetboxStatus Status;
	UPROPERTY(BlueprintReadWrite)
		FNetboxStatus Airflow;
	UPROPERTY(BlueprintReadWrite)
		FPrimaryIp Primary_ip;
	UPROPERTY(BlueprintReadWrite)
		FPrimaryIp Primary_ip4;
	UPROPERTY(BlueprintReadWrite)
		FPrimaryIp Primary_ip6;
	UPROPERTY(BlueprintReadWrite)
		FCluster Cluster;
	UPROPERTY(BlueprintReadWrite)
		FVirtualChassis Virtual_chassis;
	UPROPERTY(BlueprintReadWrite)
		int Vc_position;
	UPROPERTY(BlueprintReadWrite)
		int Vc_priority;
	UPROPERTY(BlueprintReadWrite)
		FString Comments;
	UPROPERTY(BlueprintReadWrite)
		FLocalContextData Local_context_data;
	UPROPERTY(BlueprintReadWrite)
		TArray<FTag> Tags;
	UPROPERTY(BlueprintReadWrite)
		FCustomDeviceFields Custom_fields;
	UPROPERTY(BlueprintReadWrite)
		FReztlyConfigContext Custom_context;
	UPROPERTY(BlueprintReadWrite)
		FString Created;
	UPROPERTY(BlueprintReadWrite)
		FString Last_updated; 
};

USTRUCT(BlueprintType)
struct FNetboxDeviceResponse
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
		TArray<FNetboxDevice> Results;
};