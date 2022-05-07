// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * FTextAssetTypeActions
 */
class BILLBOARDWALKER_API FTextAssetTypeActions : public FAssetTypeActions_Base
{
public:
    FTextAssetTypeActions();
    ~FTextAssetTypeActions();

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
