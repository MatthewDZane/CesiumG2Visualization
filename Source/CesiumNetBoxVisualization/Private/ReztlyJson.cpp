// Fill out your copyright notice in the Description page of Project Settings.


#include "ReztlyJson.h"

UReztlyJson::UReztlyJson()
{
	
}

TSharedPtr<FJsonObject> UReztlyJson::GetJson()
{
	return Json;
}

void UReztlyJson::SetJson(TSharedPtr<FJsonObject> JsonIn)
{
	Json = JsonIn;
}
