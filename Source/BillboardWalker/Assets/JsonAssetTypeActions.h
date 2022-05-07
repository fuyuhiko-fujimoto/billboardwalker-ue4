// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * FJsonAssetTypeActions
 */
class BILLBOARDWALKER_API FJsonAssetTypeActions : public FAssetTypeActions_Base
{
public:
    FJsonAssetTypeActions();
    ~FJsonAssetTypeActions();

    // タイプ
protected:
    virtual FText GetName() const override;
    virtual FColor GetTypeColor() const override;
    virtual uint32 GetCategories() override;

    // クラス
protected:
    virtual UClass *GetSupportedClass() const override;

    // インポート
protected:
    virtual bool IsImportedAsset() const override;

};
