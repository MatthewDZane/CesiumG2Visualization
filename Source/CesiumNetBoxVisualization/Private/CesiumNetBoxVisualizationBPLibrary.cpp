// Copyright Epic Games, Inc. All Rights Reserved.

#include "CesiumNetBoxVisualizationBPLibrary.h"
#include "CesiumNetBoxVisualization.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "ImageUtils.h"
#include "RenderUtils.h"
#include "Engine.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/Engine/Public/ShowFlags.h>

#include "RHICommandList.h"



// Static ImageWrapperModule to prevent reloading -> this thing does not like to be reloaded..
static IImageWrapperModule &ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));


UCesiumNetBoxVisualizationBPLibrary::UCesiumNetBoxVisualizationBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

int32 UCesiumNetBoxVisualizationBPLibrary::GetTexture2DDynamicWidth(UTexture2DDynamic* InTexture2DDynamicReference)
{
	if (!InTexture2DDynamicReference)
	{
		return -1;
	}

	return InTexture2DDynamicReference->SizeX;
}

int32 UCesiumNetBoxVisualizationBPLibrary::GetTexture2DDynamicHeight(UTexture2DDynamic* InTexture2DDynamicReference)
{
	if (!InTexture2DDynamicReference)
	{
		return -1;
	}

	return InTexture2DDynamicReference->SizeY;
}

void UCesiumNetBoxVisualizationBPLibrary::ExportRenderTargetAsync(const UObject* WorldContextObject, UTextureRenderTarget2D* RenderTargetToSave, const FString& FilePath, const FString& FileName, const FAsyncTaskCompletedDelegate& InCompletedDelegate)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	UCesiumNetBoxVisualizationBPLibrary::FilePathName = FilePath + FileName;

	// Get RenderContext
	FTextureRenderTargetResource* renderTargetResource = RenderTargetToSave->GameThread_GetRenderTargetResource();

	// Init new RenderRequest
	TSharedPtr<FRenderRequest> RenderRequest = MakeShared<FRenderRequest>(renderTargetResource->GetSizeXY(), FRHIGPUTextureReadback(TEXT("CameraCaptureManagerReadback")));
	
	//// Send command to GPU
	ENQUEUE_RENDER_COMMAND(SceneDrawCompletion)(
		[renderTargetResource, RenderRequest](FRHICommandListImmediate& RHICmdList) {
			FTexture2DRHIRef Target = renderTargetResource->GetRenderTargetTexture();
			RenderRequest->Readback.EnqueueCopy(RHICmdList, Target);
		});

	// Notifiy new task in RenderQueue
	UCesiumNetBoxVisualizationBPLibrary::RenderRequestQueue.Enqueue(RenderRequest);

	// Set RenderCommandFence
	RenderRequest->RenderFence.BeginFence();
	FTimerDelegate TimerDelegate;
	//TimerDelegate.CreateStatic(&UCesiumNetBoxVisualizationBPLibrary::_SaveRenderTarget);
	//World->GetTimerManager().SetTimer(UCesiumNetBoxVisualizationBPLibrary::TimerHandle, &UCesiumNetBoxVisualizationBPLibrary::_SaveRenderTarget, 1.0f, true);
	//
	//
	TimerDelegate.BindLambda([World]
	    {
	        _SaveRenderTarget(World);
	    });
	//TimerDelegate.CreateStatic(&USetupDeviceTextureAsync::_SaveRenderTarget, RenderRequest);
	World->GetTimerManager().SetTimer(UCesiumNetBoxVisualizationBPLibrary::TimerHandle, TimerDelegate, 1.0f, true);


}

void UCesiumNetBoxVisualizationBPLibrary::RunAsyncImageSaveTask(TArray<uint8, FDefaultAllocator64> Image, FString ImageName)
{
	(new FAutoDeleteAsyncTask<AsyncSaveImageToDiskTask>(Image, ImageName))->StartBackgroundTask();
}

void UCesiumNetBoxVisualizationBPLibrary::_SaveRenderTarget(UWorld* World)
{
	// Read pixels once RenderFence is completed
	if (!UCesiumNetBoxVisualizationBPLibrary::RenderRequestQueue.IsEmpty()) {
		// Peek the next RenderRequest from queue
		TSharedPtr<FRenderRequest> nextRenderRequest = *RenderRequestQueue.Peek();

		int32 frameWidht = 2048;
		int32 frameHeight = 2048;

		if (nextRenderRequest) { //nullptr check
			if (nextRenderRequest->RenderFence.IsFenceComplete() && nextRenderRequest->Readback.IsReady()) { // Check if rendering is done, indicated by RenderFence & Readback

				World->GetTimerManager().ClearTimer(UCesiumNetBoxVisualizationBPLibrary::TimerHandle);

				AsyncTask(ENamedThreads::AnyHiPriThreadHiPriTask, [=]() {
					FOptionalTaskTagScope Scope(ETaskTag::EParallelRenderingThread);

				// Load the image wrapper module 
				IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

				// Get Data from Readback
				int32 RawSize = nextRenderRequest->ImageSize.X * nextRenderRequest->ImageSize.Y * sizeof(FColor);
				void* RawData = nextRenderRequest->Readback.Lock(RawSize);

				// Prepare data to be written to disk
				static TSharedPtr<IImageWrapper> imageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG); //EImageFormat::PNG //EImageFormat::JPEG
				imageWrapper->SetRaw(RawData, RawSize, 2048, 2048, ERGBFormat::BGRA, 8);

				const TArray<uint8, FDefaultAllocator64>& ImgData = imageWrapper->GetCompressed(5);
				RunAsyncImageSaveTask(ImgData, UCesiumNetBoxVisualizationBPLibrary::FilePathName);

				if (!UCesiumNetBoxVisualizationBPLibrary::FilePathName.IsEmpty()) {
					UE_LOG(LogTemp, Warning, TEXT("%f"), *UCesiumNetBoxVisualizationBPLibrary::FilePathName);
				}

				// Delete the first element from RenderQueue
				UCesiumNetBoxVisualizationBPLibrary::RenderRequestQueue.Pop();

				UE_LOG(LogTemp, Log, TEXT("Done..."));
					});
			}
		}
	}
		
}

/*

(new FAutoDeleteAsyncTask<FAsyncExportRenderTargetTask>(RenderTargetToSave, FilePath, FileName, InCompletedDelegate))->StartBackgroundTask();

uint32 TextureSizeX = 1024;
uint32 TextureSizeY = 1024;
EPixelFormat TextureFormat = PF_B8G8R8A8;
UTexture2D* DeviceTexture = UTexture2D::CreateTransient(TextureSizeX, TextureSizeY, TextureFormat);

AsyncTask(ENamedThreads::AnyThread, [RenderTargetToSave, FilePath, FileName, InCompletedDelegate, DeviceTexture]()
{
		InCompletedDelegate.ExecuteIfBound(DeviceTexture);

	//AsyncTask(ENamedThreads::GameThread, [InCompletedDelegate, DeviceTexture]()
	//{
	//		InCompletedDelegate.ExecuteIfBound(DeviceTexture);
	//});
});

*/