#pragma once

#include "NetboxResponse.generated.h"

USTRUCT(BlueprintType)
struct FTag
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
		FString Color;
};

USTRUCT(BlueprintType)
struct FTenant
{
	GENERATED_USTRUCT_BODY()
public:
};

USTRUCT(BlueprintType)
struct FNetboxStatus
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FString Value;
	UPROPERTY(BlueprintReadWrite)
		FString Label;
};

USTRUCT(BlueprintType)
struct FNetboxType
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FString Value;
	UPROPERTY(BlueprintReadWrite)
		FString Label;
};

USTRUCT(BlueprintType)
struct FNetboxWidth
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FString Value;
	UPROPERTY(BlueprintReadWrite)
		FString Label;
};


