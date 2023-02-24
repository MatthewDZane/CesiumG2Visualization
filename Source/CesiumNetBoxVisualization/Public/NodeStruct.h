// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NodeStruct.generated.h"

USTRUCT(BlueprintType)
struct FNodeStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FString ID;
	UPROPERTY(BlueprintReadWrite)
		FString Info;
	UPROPERTY(BlueprintReadWrite)
		FString Name;
	UPROPERTY(BlueprintReadWrite)
		FString IP;
	UPROPERTY(BlueprintReadWrite)
		bool Primary;
	UPROPERTY(BlueprintReadWrite)
		int MTU;
	UPROPERTY(BlueprintReadWrite)
		FString DeviceName;
	UPROPERTY(BlueprintReadWrite)
		TArray<FString> LinkedNodeIDs;
};