// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/Texture2DDynamic.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Engine/Engine.h"
#include "Delegates/Delegate.h"
#include <BufferArchive.h>
#include <ImageUtils.h>
#include "CesiumNetBoxVisualizationBPLibrary.generated.h"


/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

DECLARE_DYNAMIC_DELEGATE_OneParam(FAsyncTaskCompletedDelegate, UTexture2D*, Texture2D);

class FAsyncExportRenderTargetTask : public FNonAbandonableTask
{
    friend class FAutoDeleteAsyncTask<FAsyncExportRenderTargetTask>;

public:

    UTextureRenderTarget2D* RenderTarget;
    FString FilePath;
    FString FileName;
    FAsyncTaskCompletedDelegate CompletedDelegate;

    FAsyncExportRenderTargetTask(UTextureRenderTarget2D* InRenderTarget, const FString& inFilePath, const FString& inFileName, const FAsyncTaskCompletedDelegate& InCompletedDelegate)
        : RenderTarget(InRenderTarget),
        FilePath(inFilePath),
        FileName(inFileName),
        CompletedDelegate(InCompletedDelegate)
    {
    }
protected:
    void DoWork()
    {
        FTaskTagScope Scope(ETaskTag::EParallelRenderingThread);
        UTexture2D* LoadedTexture = nullptr;

        if (RenderTarget != nullptr)
        {
            //UKismetRenderingLibrary::ExportRenderTarget(GEngine->GetWorld(), RenderTarget, FilePath, FileName);
            FString TotalFileName = FPaths::Combine(*FilePath, *FileName);
            FText PathError;
            FPaths::ValidatePath(TotalFileName, &PathError);

            FArchive* Ar = IFileManager::Get().CreateFileWriter(*TotalFileName);

            if (Ar)
            {
                FBufferArchive Buffer;

                bool bSuccess = FImageUtils::ExportRenderTarget2DAsPNG(RenderTarget, Buffer);

                if (bSuccess)
                {
                    Ar->Serialize(const_cast<uint8*>(Buffer.GetData()), Buffer.Num());
                }

                delete Ar;
            }

            //UKismetRenderingLibrary::ClearRenderTarget2D(GEngine->GetWorld(), RenderTarget);
            //LoadedTexture = UKismetRenderingLibrary::ImportFileAsTexture2D(GEngine->GetWorld(), FilePath.Append(FileName));
            //
            //// Call the completion delegate with the loaded texture
            //if (CompletedDelegate.IsBound())
            //{
            //    CompletedDelegate.Execute(LoadedTexture);
            //}

        }
    }

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FAsyncExportRenderTargetTask, STATGROUP_ThreadPoolAsyncTasks);
    }
};

class FAsyncImportTextureTask : public FNonAbandonableTask
{
    friend class FAutoDeleteAsyncTask<FAsyncImportTextureTask>;

public:
    FString FilePath;
    FString Filename;
    FAsyncTaskCompletedDelegate CompletedDelegate;

    FAsyncImportTextureTask(const FString& inFilePath, const FString& inFileName, const FAsyncTaskCompletedDelegate& InCompletedDelegate)
        : FilePath(inFilePath),
        Filename(inFileName),
        CompletedDelegate(InCompletedDelegate)
    {
    }

protected:
    void DoWork()
    {
    }

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FAsyncExportRenderTargetTask, STATGROUP_ThreadPoolAsyncTasks);
    }
};


class AsyncSaveImageToDiskTask : public FNonAbandonableTask {
public:
    AsyncSaveImageToDiskTask(TArray<uint8, FDefaultAllocator64> Image, FString ImageName)
        :ImageCopy(Image),
         FileName(ImageName)
    {
    }
    ~AsyncSaveImageToDiskTask()
    {
    }

    FORCEINLINE TStatId GetStatId() const {
        RETURN_QUICK_DECLARE_CYCLE_STAT(AsyncSaveImageToDiskTask, STATGROUP_ThreadPoolAsyncTasks);
    }

protected:
    TArray<uint8> ImageCopy;
    FString FileName = "";

public:
    void DoWork()
    {
        FFileHelper::SaveArrayToFile(ImageCopy, *FileName);
        UE_LOG(LogTemp, Log, TEXT("Stored Image: %s"), *FileName);
    }
};

struct FRenderRequest {
    FIntPoint ImageSize;
    FRHIGPUTextureReadback Readback;
    FRenderCommandFence RenderFence;

    FRenderRequest(
        const FIntPoint& ImageSize,
        const FRHIGPUTextureReadback& Readback) :
        ImageSize(ImageSize),
        Readback(Readback) {}
};

UCLASS()
class UCesiumNetBoxVisualizationBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable)
		static int32 GetTexture2DDynamicWidth(UTexture2DDynamic* InTexture2DDynamicReference);
	UFUNCTION(BlueprintCallable)
		static int32 GetTexture2DDynamicHeight(UTexture2DDynamic* InTexture2DDynamicReference);

    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
        static void ExportRenderTargetAsync(const UObject* WorldContextObject, UTextureRenderTarget2D* RenderTargetToSave, const FString& FilePath, const FString& FileName, const FAsyncTaskCompletedDelegate& InCompletedDelegate);

    protected:
        // Creates an async task that will save the captured image to disk
        static void RunAsyncImageSaveTask(TArray<uint8, FDefaultAllocator64> Image, FString ImageName);

    private:
        static inline TQueue<TSharedPtr<FRenderRequest>> RenderRequestQueue;
        static void _SaveRenderTarget(UWorld* World);
        static inline FTimerHandle TimerHandle;
        static inline FString FilePathName;
};