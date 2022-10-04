// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "G2Topology.generated.h"

UCLASS(Abstract, Blueprintable)
class CESIUMG2VISUALIZATION_API AG2Topology : public AActor
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI")
		void HideDisplays();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, BlueprintPure, Category="Utility")
		FRotator GetRotationRelativeToSurface(FVector Location);

};
