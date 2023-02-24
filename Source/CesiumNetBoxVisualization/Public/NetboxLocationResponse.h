// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetboxResponse.h"

#include "NetboxLocationResponse.generated.h"

USTRUCT(BlueprintType)
struct FLocationSite
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
struct FLocationParent
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
struct FCustomLocationFields
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FString Location_world_location_offset;
	UPROPERTY(BlueprintReadWrite)
		FString Location_world_rotation_offset;
};

USTRUCT(BlueprintType)
struct FLocationStruct
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
		FLocationSite Site;
	UPROPERTY(BlueprintReadWrite)
		FLocationParent Parent;
	UPROPERTY(BlueprintReadWrite)
		FTenant Tenant;
	UPROPERTY(BlueprintReadWrite)
		TArray<FTag> Tags;
	UPROPERTY(BlueprintReadWrite)
		FCustomLocationFields Custom_fields;
	UPROPERTY(BlueprintReadWrite)
		FString Created;
	UPROPERTY(BlueprintReadWrite)
		FString Last_updated;
	UPROPERTY(BlueprintReadWrite)
		int Rack_count;
	UPROPERTY(BlueprintReadWrite)
		int Device_count;
	UPROPERTY(BlueprintReadWrite)
		int _depth;
};

USTRUCT(BlueprintType)
struct FNetboxLocationResponse
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
		TArray<FLocationStruct> Results;
};