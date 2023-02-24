#pragma once

#include "Avatars.generated.h"

USTRUCT(BlueprintType)
struct FAvatarStruct
{
    GENERATED_USTRUCT_BODY()

    FAvatarStruct() : Name(TEXT("")), ID(TEXT("")){}

    UPROPERTY(BlueprintReadWrite, Category = "Reztly")
        FString Name;

    UPROPERTY(BlueprintReadWrite, Category = "Reztly")
        FString ID;
};

USTRUCT(BlueprintType)
struct FAvatarArrayStruct
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Reztly")
        TArray<FAvatarStruct> Avatars;
};