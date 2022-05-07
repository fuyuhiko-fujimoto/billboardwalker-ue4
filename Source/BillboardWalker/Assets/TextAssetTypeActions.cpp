// Fill out your copyright notice in the Description page of Project Settings.


#include "TextAssetTypeActions.h"
#include "Assets/TextAsset.h"

FTextAssetTypeActions::FTextAssetTypeActions()
{
}

FTextAssetTypeActions::~FTextAssetTypeActions()
{
}

// タイプの名前を返す
FText FTextAssetTypeActions::GetName() const
{
    return NSLOCTEXT("AssetTypeActions", "FTextAssetTypeActions", "Text Asset");
}

// タイプの名前を返す
FColor FTextAssetTypeActions::GetTypeColor() const
{
    return FColor::White;
}

// タイプのカテゴリを返す
uint32 FTextAssetTypeActions::GetCategories()
{
    return EAssetTypeCategories::Misc;
}

// サポートされたクラスを返す
UClass *FTextAssetTypeActions::GetSupportedClass() const
{
    return UTextAsset::StaticClass();
}

// アセットがインポートできるかどうかを返す
bool FTextAssetTypeActions::IsImportedAsset() const
{
    return true;
}
