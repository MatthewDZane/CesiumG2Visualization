// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "G2SnapshotResponse.generated.h"

USTRUCT(BlueprintType)
struct FG2NodeStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FString ID;
	UPROPERTY(BlueprintReadWrite)
	FString Info;
	UPROPERTY(BlueprintReadWrite)
	FString Lat;
	UPROPERTY(BlueprintReadWrite)
	FString Lng;
	UPROPERTY(BlueprintReadWrite)
	FString Name;
};

USTRUCT(BlueprintType)
struct FLink
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FString Bandwidth;
	UPROPERTY(BlueprintReadWrite)
	FString Delay;
	UPROPERTY(BlueprintReadWrite)
	int Group;
	UPROPERTY(BlueprintReadWrite)
	FString ID;
	UPROPERTY(BlueprintReadWrite)
	FString Info;
	UPROPERTY(BlueprintReadWrite)
	int Loss;
	UPROPERTY(BlueprintReadWrite)
	FString Max_queue_size;
	UPROPERTY(BlueprintReadWrite)
	FString Source;
	UPROPERTY(BlueprintReadWrite)
	FString Target;
	UPROPERTY(BlueprintReadWrite)
	FString Use_htb;
};

USTRUCT(BlueprintType)
struct FTopology
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FLink> Links;
	UPROPERTY(BlueprintReadWrite)
	TArray<FG2NodeStruct> Nodes;
};

USTRUCT(BlueprintType)
struct FTopo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FTopology Topology;
	UPROPERTY(BlueprintReadWrite)
	int With_location;
};

USTRUCT(BlueprintType)
struct FQOSClasses
{
	GENERATED_USTRUCT_BODY()
public:
};

USTRUCT(BlueprintType)
struct FImpact
{
	GENERATED_USTRUCT_BODY()
public:
};

USTRUCT(BlueprintType)
struct FFlowLink
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int Group;
	UPROPERTY(BlueprintReadWrite)
	FString ID;
	UPROPERTY(BlueprintReadWrite)
	FString Source;
	UPROPERTY(BlueprintReadWrite)
	FString Target;
};

USTRUCT(BlueprintType)
struct FFlow
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FString End;
	UPROPERTY(BlueprintReadWrite)
	FString Exp_share;
	UPROPERTY(BlueprintReadWrite)
	FString Id;
	UPROPERTY(BlueprintReadWrite)
	FString Info;
	UPROPERTY(BlueprintReadWrite)
	TArray<FFlowLink> Links;
	UPROPERTY(BlueprintReadWrite)
	int Num_bytes;
	UPROPERTY(BlueprintReadWrite)
	int Num_flows;
	UPROPERTY(BlueprintReadWrite)
	FQOSClasses Qos_class;
	UPROPERTY(BlueprintReadWrite)
	FString Start;
	UPROPERTY(BlueprintReadWrite)
	float Start_time;
};

USTRUCT(BlueprintType)
struct FFlows
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FFlow> Flowgroups;
	UPROPERTY(BlueprintReadWrite)
	int Num_flowGroups;
};

USTRUCT(BlueprintType)
struct FFGGTree
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int Fairshare;
	UPROPERTY(BlueprintReadWrite)
	float Gradient;
	UPROPERTY(BlueprintReadWrite)
	FString ID;
	UPROPERTY(BlueprintReadWrite)
	int Level;
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> Out;
	UPROPERTY(BlueprintReadWrite)
	FString Type;
};

USTRUCT(BlueprintType)
struct FFGG
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int Level;
	UPROPERTY(BlueprintReadWrite)
	TArray<FFGGTree> Tree;
};

USTRUCT(BlueprintType)
struct FBPGTree
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int Fairshare;
	UPROPERTY(BlueprintReadWrite)
	FString Gradient;
	UPROPERTY(BlueprintReadWrite)
	FString ID;
	UPROPERTY(BlueprintReadWrite)
	int Level;
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> Out_direct;
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> Out_indirect;
	UPROPERTY(BlueprintReadWrite)
	FString Type;
};

USTRUCT(BlueprintType)
struct FBPG
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int Level;
	UPROPERTY(BlueprintReadWrite)
	TArray<FBPGTree> Tree;
};

USTRUCT(BlueprintType)
struct FSnapshot
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FBPG Bpg;
	UPROPERTY(BlueprintReadWrite)
	FFGG Fgg;
	UPROPERTY(BlueprintReadWrite)
	FFlows Flows;
	UPROPERTY(BlueprintReadWrite)
	int Id;
	UPROPERTY(BlueprintReadWrite)
	FImpact Impact;
	UPROPERTY(BlueprintReadWrite)
	int Parent_id;
	UPROPERTY(BlueprintReadWrite)
	FQOSClasses Qos_classes;
	UPROPERTY(BlueprintReadWrite)
	FTopo Topo;
};

USTRUCT(BlueprintType)
struct FData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int Num_snapshots;
	UPROPERTY(BlueprintReadWrite)
	TArray<FSnapshot> Snapshots;
};

USTRUCT(BlueprintType)
struct FG2SnapshotResponse
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FData Data;
	UPROPERTY(BlueprintReadWrite)
	FString Type;
};