// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonAssetTypeActions.h"
#include "Assets/JsonAsset.h"

FJsonAssetTypeActions::FJsonAssetTypeActions()
{
}

FJsonAssetTypeActions::~FJsonAssetTypeActions()
{
}

// タイプの名前を返す
FText FJsonAssetTypeActions::GetName() const
{
    return NSLOCTEXT("AssetTypeActions", "FJsonAssetTypeActions", "Json Asset");
}

// タイプの名前を返す
FColor FJsonAssetTypeActions::GetTypeColor() const
{
    return FColor::White;
}

// タイプのカテゴリを返す
uint32 FJsonAssetTypeActions::GetCategories()
{
    return EAssetTypeCategories::Misc;
}

// サポートされたクラスを返す
UClass *FJsonAssetTypeActions::GetSupportedClass() const
{
    return UJsonAsset::StaticClass();
}

// アセットがインポートできるかどうかを返す
bool FJsonAssetTypeActions::IsImportedAsset() const
{
    return true;
}
    

