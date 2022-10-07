// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "G2SnapshotResponse.h"
#include "G2Node.h"

#include "G2Snapshot.generated.h"


USTRUCT(BlueprintType)
struct FG2Link
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		float Bandwidth;
	UPROPERTY(BlueprintReadWrite)
		float Delay;

	UPROPERTY(BlueprintReadWrite)
		int Group;

	UPROPERTY(BlueprintReadWrite)
		FString ID;
	UPROPERTY(BlueprintReadWrite)
		FString Info;

	UPROPERTY(BlueprintReadWrite)
		int Loss;

	UPROPERTY(BlueprintReadWrite)
		FString MaxQueueSize;
	UPROPERTY(BlueprintReadWrite)
		FString UseHTB;

	UPROPERTY(BlueprintReadWrite)
		UG2Node* Source;

	UPROPERTY(BlueprintReadWrite)
		UG2Node* Target;
};

UCLASS(Blueprintable)
class CESIUMNETBOXVISUALIZATION_API UG2Snapshot : public UObject
{
	GENERATED_BODY()

public:
	UG2Snapshot();
	~UG2Snapshot();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	    TMap<FString, UG2Node*> IDToNodeMap;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FG2Link> Links;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FFlow> Flows;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int ID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int TimeStamp;

	void CopyData(UG2Snapshot* G2SnapshotIn);
};
