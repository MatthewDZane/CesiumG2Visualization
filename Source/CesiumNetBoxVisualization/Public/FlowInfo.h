#pragma once

#include "FlowInfo.generated.h"

USTRUCT(BlueprintType)
struct FFlowInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		FString Src_ip;
	UPROPERTY(BlueprintReadWrite)
		FString Src_port;
	UPROPERTY(BlueprintReadWrite)
		FString Dst_ip;
	UPROPERTY(BlueprintReadWrite)
		FString Dst_port;
	UPROPERTY(BlueprintReadWrite)
		FString Src_ns;
	UPROPERTY(BlueprintReadWrite)
		FString Src_pod;
	UPROPERTY(BlueprintReadWrite)
		FString Src_containers;
	UPROPERTY(BlueprintReadWrite)
		FString Dst_ns;
	UPROPERTY(BlueprintReadWrite)
		FString Dst_pod;
	UPROPERTY(BlueprintReadWrite)
		FString Dst_containers;
};