// Fill out your copyright notice in the Description page of Project Settings.


#include "SetupDeviceTextureAsync.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Canvas.h"
#include "Kismet/KismetRenderingLibrary.h"
#include <Runtime/Engine/Public/ShowFlags.h>

#include "RHICommandList.h"

#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "ImageUtils.h"

USetupDeviceTextureAsync* USetupDeviceTextureAsync::SetupDeviceTextureAsync(const UObject* WorldContextObject, UTextureRenderTarget2D* RenderTarget, FString FilePath, FString FileName)
{
    USetupDeviceTextureAsync* SetupDeviceTextureAsyncNode = NewObject<USetupDeviceTextureAsync>();
    SetupDeviceTextureAsyncNode->RenderTarget = RenderTarget;
    SetupDeviceTextureAsyncNode->FilePathName = FilePath.Append(FileName);
    SetupDeviceTextureAsyncNode->WorldContextObject = WorldContextObject;
    SetupDeviceTextureAsyncNode->RegisterWithGameInstance(WorldContextObject);

    return SetupDeviceTextureAsyncNode;
}

void USetupDeviceTextureAsync::Activate()
{
    // Any safety checks should be performed here. Check here validity of all your pointers etc.
    // You can log any errors using FFrame::KismetExecutionMessage, like that:
    // FFrame::KismetExecutionMessage(TEXT("Valid Player Controller reference is needed for ... to start!"), ELogVerbosity::Error);
    // return;

    AsyncTask(ENamedThreads::AnyBackgroundHiPriTask, [=]() {
        FTaskTagScope Scope(ETaskTag::EAsyncLoadingThread);

    ///code here





    if (nullptr == WorldContextObject)
    {
        FFrame::KismetExecutionMessage(TEXT("Invalid WorldContextObject. Cannot execute."), ELogVerbosity::Error);
        return;
    }
    
    // Get RenderConterxtS
    FTextureRenderTargetResource* renderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();

    // Init new RenderRequest
    TSharedPtr<FRenderRequest2> RenderRequest = MakeShared<FRenderRequest2>(renderTargetResource->GetSizeXY(), FRHIGPUTextureReadback(TEXT("CameraCaptureManagerReadback")));

    // Send command to GPU
    ENQUEUE_RENDER_COMMAND(SceneDrawCompletion)(
        [renderTargetResource, RenderRequest](FRHICommandListImmediate& RHICmdList) {
            FTexture2DRHIRef Target = renderTargetResource->GetRenderTargetTexture();
    RenderRequest->Readback.EnqueueCopy(RHICmdList, Target);
        });

    // Set RenderCommandFence
    RenderRequest->RenderFence.BeginFence(true);

    _SaveRenderTarget(RenderRequest);

    //FTimerDelegate TimerDelegate;
    //TimerDelegate.BindLambda([this, RenderRequest]
    //    {
    //        _SaveRenderTarget(RenderRequest);
    //    });
    ////TimerDelegate.CreateStatic(&USetupDeviceTextureAsync::_SaveRenderTarget, RenderRequest);
    //WorldContextObject->GetWorld()->GetTimerManager().SetTimer(Timer, TimerDelegate, 1.0f, true);
    //
        });
    
}

void USetupDeviceTextureAsync::_SaveRenderTarget(TSharedPtr<FRenderRequest2> RenderRequest)
{
    if (RenderRequest->RenderFence.IsFenceComplete() && RenderRequest->Readback.IsReady())
    {
        WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(Timer);

        // Load the image wrapper module 
        IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

        // Get Data from Readback
        int32 RawSize = RenderRequest->ImageSize.X * RenderRequest->ImageSize.Y * sizeof(FColor);
        void* RawData = RenderRequest->Readback.Lock(RawSize);

        // Prepare data to be written to disk
        static TSharedPtr<IImageWrapper> imageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG); //EImageFormat::PNG //EImageFormat::JPEG
        imageWrapper->SetRaw(RawData, RawSize, 1024, 1024, ERGBFormat::BGRA, 8);
        const TArray64<uint8>& ImgData = imageWrapper->GetCompressed(5);

        if (FFileHelper::SaveArrayToFile(ImgData, *FilePathName))
        {
            UE_LOG(LogTemp, Log, TEXT("Stored Image: %s"), *FilePathName);
            OnSuccess.Broadcast();
            SetReadyToDestroy();
        }
        else 
        {
            UE_LOG(LogTemp, Log, TEXT("Failed Image: %s"), *FilePathName);
            OnFail.Broadcast();
            SetReadyToDestroy();
        }

    }
}
