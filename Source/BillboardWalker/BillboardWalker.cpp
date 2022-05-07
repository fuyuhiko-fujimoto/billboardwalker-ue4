// Fill out your copyright notice in the Description page of Project Settings.

#include "BillboardWalker.h"
#include "Modules/ModuleManager.h"
#include "Assets/JsonAssetTypeActions.h"
#include "Assets/TextAssetTypeActions.h"

// IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, BillboardWalker, "BillboardWalker" );

class FBillboardWalker : public FDefaultGameModuleImpl
{
    // モジュール
private:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    // アセットアクション
private:
    TSharedPtr<FJsonAssetTypeActions> jsonAssetTypeActions_;
    TSharedPtr<FTextAssetTypeActions> textAssetTypeActions_;
};
IMPLEMENT_PRIMARY_GAME_MODULE( FBillboardWalker, BillboardWalker, "BillboardWalker" );

// モジュールが読み込まれたときに呼び出される
void FBillboardWalker::StartupModule()
{
    // Json アセットアクションの追加
    jsonAssetTypeActions_ = MakeShareable(new FJsonAssetTypeActions);
    FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools")
        .Get()
        .RegisterAssetTypeActions(jsonAssetTypeActions_.ToSharedRef());

    // Text アセットアクションの追加
    textAssetTypeActions_ = MakeShareable(new FTextAssetTypeActions);
    FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools")
        .Get()
        .RegisterAssetTypeActions(textAssetTypeActions_.ToSharedRef());
}

// モジュールが破棄されたときに呼び出される
void FBillboardWalker::ShutdownModule()
{
    // Json アセットアクションの削除
    if (jsonAssetTypeActions_.IsValid()) {
        if (FModuleManager::Get().IsModuleLoaded("AssetTools")) {
            FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools")
                .Get()
                .UnregisterAssetTypeActions(jsonAssetTypeActions_.ToSharedRef());
        }
        jsonAssetTypeActions_.Reset();
    }

    // Text アセットアクションの削除
    if (textAssetTypeActions_.IsValid()) {
        if (FModuleManager::Get().IsModuleLoaded("AssetTools")) {
            FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools")
                .Get()
                .UnregisterAssetTypeActions(textAssetTypeActions_.ToSharedRef());
        }
        textAssetTypeActions_.Reset();
    }
}

