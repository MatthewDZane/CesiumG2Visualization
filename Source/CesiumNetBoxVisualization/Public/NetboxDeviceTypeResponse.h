#pragma once

#include "NetboxResponse.h"

#include "NetboxDeviceTypeResponse.generated.h"

USTRUCT(BlueprintType)
struct FCustomDeviceTypeFields
{
	GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType)
struct FManufacturer
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
struct FNetboxDeviceType
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
		TArray<FTag> Tags;
	UPROPERTY(BlueprintReadWrite)
		FCustomDeviceTypeFields Custom_fields;
	UPROPERTY(BlueprintReadWrite)
		FString Created;
	UPROPERTY(BlueprintReadWrite)
		FString Last_updated;
	UPROPERTY(BlueprintReadWrite)
		int Device_count;
};

USTRUCT(BlueprintType)
struct FNetboxDeviceTypeResponse
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
		TArray<FNetboxDeviceType> Results;
};