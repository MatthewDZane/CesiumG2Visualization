// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Delegates/Delegate.h"
#include "Engine/Texture2DDynamic.h"
#include "SetupDeviceTextureAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSetupDeviceTextureOutputPin);

struct FRenderRequest2 {

	FIntPoint ImageSize;
	FRHIGPUTextureReadback Readback;
	FRenderCommandFence RenderFence;

	FRenderRequest2(
		const FIntPoint& ImageSize,
		const FRHIGPUTextureReadback& Readback) :
		ImageSize(ImageSize),
		Readback(Readback) {}
};

UCLASS()
class CESIUMNETBOXVISUALIZATION_API USetupDeviceTextureAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(BlueprintAssignable)
	FSetupDeviceTextureOutputPin OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FSetupDeviceTextureOutputPin OnFail;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Flow Control")
		static USetupDeviceTextureAsync* SetupDeviceTextureAsync(const UObject* WorldContextObject, UTextureRenderTarget2D* RenderTarget, FString FilePath, FString FileName);
	
	virtual void Activate() override;

private:
	UTextureRenderTarget2D* RenderTarget;
	FString FilePathName;
	FTimerHandle Timer;
	const UObject* WorldContextObject;

	void _SaveRenderTarget(TSharedPtr<FRenderRequest2> RenderRequest);
};