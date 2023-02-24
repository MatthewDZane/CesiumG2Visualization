// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Device.h"

#include "G2Node.generated.h"

/**
 * 
 */
UCLASS()
class CESIUMNETBOXVISUALIZATION_API UG2Node : public UObject
{
	GENERATED_BODY()

public:
	UG2Node();
	UG2Node(
		FString IDIn, 
		FString InfoIn, 
		FString NameIn, 
		FString IPIn,
		float LatitudeIn,
		float LongitudeIn, 
		bool PrimaryIn, 
		int MTUIn
	);
	~UG2Node();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString ID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Info;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString IP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Latitude;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Longitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Primary;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MTU;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UDevice* Device;
};
