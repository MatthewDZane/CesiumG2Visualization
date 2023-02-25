// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4Response.generated.h"
USTRUCT(BlueprintType)
struct FPath
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		TArray<FString> Values;
};

USTRUCT(BlueprintType)
struct FUE4Edge
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		int Source;
	UPROPERTY(BlueprintReadWrite)
		int Target;
	UPROPERTY(BlueprintReadWrite)
		int Mtu;
	UPROPERTY(BlueprintReadWrite)
		float Latency;
	// should be some form of nested array but Unreal doesn't support it
	UPROPERTY(BlueprintReadWrite)
		TArray<FPath> Paths;
};

USTRUCT(BlueprintType)
struct FUE4Node
{
	GENERATED_USTRUCT_BODY()
public:
	// should be some form of nested array but Unreal doesn't support it
	UPROPERTY(BlueprintReadWrite)
		TArray<FPath> Paths;
	UPROPERTY(BlueprintReadWrite)
		FString Hostname;
	UPROPERTY(BlueprintReadWrite)
		FString Ip;
	UPROPERTY(BlueprintReadWrite)
		float Latitude;
	UPROPERTY(BlueprintReadWrite)
		float Longitude;
	UPROPERTY(BlueprintReadWrite)
		bool Primary;
};

USTRUCT(BlueprintType)
struct FUE4Response
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		TArray<FUE4Node> Nodes;
	UPROPERTY(BlueprintReadWrite)
		TArray<FUE4Edge> Edges;
};