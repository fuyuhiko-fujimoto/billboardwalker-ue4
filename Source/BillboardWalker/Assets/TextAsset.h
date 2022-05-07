// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TextAsset.generated.h"

/**
 * UTextAsset
 */
UCLASS()
class BILLBOARDWALKER_API UTextAsset : public UObject
{
    GENERATED_BODY()
    
    // ソース
protected:
    UPROPERTY(VisibleAnywhere, Category = "Text")
    FString sourcePath_;
public:
    FString &GetSourcePath();
    void SetSourcePath(const FString &path);

    // 文字列
protected:
    UPROPERTY(VisibleAnywhere, Category = "Text")
    FString string_;
public:
    FString GetString();
    bool SetString(const FString &string);

};
