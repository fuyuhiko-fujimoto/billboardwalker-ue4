// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dom/JsonObject.h"
#include "JsonAsset.generated.h"

/**
 * UJsonAsset
 */
UCLASS()
class BILLBOARDWALKER_API UJsonAsset : public UObject
{
    GENERATED_BODY()
    
    // ソース
protected:
    UPROPERTY(VisibleAnywhere, Category = "Json")
    FString sourcePath_;
public:
    FString &GetSourcePath();
    void SetSourcePath(const FString &path);

    // 文字列
protected:
    UPROPERTY(VisibleAnywhere, Category = "Json")
    FString string_;
public:
    FString &GetString();
    bool SetString(const FString &string);

    // Json オブジェクト
public:
    TSharedPtr<FJsonObject> GetJsonObject();

};
