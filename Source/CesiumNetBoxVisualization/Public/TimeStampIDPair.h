// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimeStampIDPair.generated.h"

USTRUCT(BlueprintType)
struct FTimeStampIDPair
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		int TimeStamp;
	UPROPERTY(BlueprintReadWrite)
		int ID;
};