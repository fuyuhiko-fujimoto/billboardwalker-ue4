// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonAssetFactory.h"
#include "Misc/FileHelper.h"
#include "EditorFramework/AssetImportData.h"


// コンストラクタ
UJsonAssetFactory::UJsonAssetFactory()
    : UFactory(), FReimportHandler()
{
    Formats.Add(FString(TEXT("json;")) + NSLOCTEXT("UJsonAssetFactory", "FormatJson", "Json Object").ToString());
    SupportedClass = UJsonAsset::StaticClass();
    bCreateNew = false;
    bEditorImport = true;
}

// ファイルをインポートしてクラスオブジェクトを作成する
UObject *UJsonAssetFactory::FactoryCreateFile(UClass *InClass, UObject *InParent, FName InName, EObjectFlags Flags, const FString &Filename, const TCHAR *Parms, FFeedbackContext *Warn, bool & bOutOperationCanceled)
{
    UJsonAsset *jsonAsset = NewObject<UJsonAsset>(InParent, InClass, InName, Flags);
    if (jsonAsset != nullptr) {
        if (Import(jsonAsset, Filename)) {
            UE_LOG(LogTemp, Log, TEXT("UJsonAssetFactory::FactoryCreateFile() - import file: %s"), *Filename);
        } else {
            UE_LOG(LogTemp, Log, TEXT("UJsonAssetFactory::FactoryCreateFile() - invalid json file: %s"), *Filename);
        }
    } else {
        UE_LOG(LogTemp, Log, TEXT("UJsonAssetFactory::FactoryCreateFile() - no object."));
    }
    bOutOperationCanceled = false;
    return jsonAsset;
}

// ファイルからアセットをインポートする
bool UJsonAssetFactory::Import(UJsonAsset *asset, const FString &path)
{
    bool result = false;
    FString string;
    if (FFileHelper::LoadFileToString(string, *path)) {
        if (asset->SetString(string)) {
            asset->SetSourcePath(UAssetImportData::SanitizeImportFilename(CurrentFilename, asset->GetOutermost()));
            result = true;
        }
    }
    return result;
}

// 再インポート可能かどうかを判定する
bool UJsonAssetFactory::CanReimport(UObject *Obj, TArray<FString> &OutFilenames)
{
    bool result = false;
    UJsonAsset *jsonAsset = Cast<UJsonAsset>(Obj);
    if (jsonAsset != nullptr) {
        OutFilenames.Add(UAssetImportData::ResolveImportFilename(jsonAsset->GetSourcePath(), jsonAsset->GetOutermost()));
        result = true;
        UE_LOG(LogTemp, Log, TEXT("UJsonAssetFactory::CanReimport() - check file: %s"), *jsonAsset->GetSourcePath());
    } else {
        UE_LOG(LogTemp, Log, TEXT("UJsonAssetFactory::CanReimport() - no object."));
    }
    return result;
}

// 再インポートするパスを設定する
void UJsonAssetFactory::SetReimportPaths(UObject *Obj, const TArray< FString > & NewReimportPaths)
{
    UJsonAsset *jsonAsset = Cast<UJsonAsset>(Obj);
    if (jsonAsset != nullptr && ensure(NewReimportPaths.Num() == 1)) {
        jsonAsset->SetSourcePath(UAssetImportData::SanitizeImportFilename(NewReimportPaths[0], jsonAsset->GetOutermost()));
        UE_LOG(LogTemp, Log, TEXT("UJsonAssetFactory::SetReimportPaths() - import file: %s"), *jsonAsset->GetSourcePath());
    } else {
        UE_LOG(LogTemp, Log, TEXT("UJsonAssetFactory::SetReimportPaths() - no object."));
    }
}

// 再インポートする
EReimportResult::Type UJsonAssetFactory::Reimport(UObject *Obj)
{
    EReimportResult::Type result = EReimportResult::Failed;
    UJsonAsset *jsonAsset = Cast<UJsonAsset>(Obj);
    if (jsonAsset != nullptr) {
        const FString filename = UAssetImportData::ResolveImportFilename(jsonAsset->GetSourcePath(), jsonAsset->GetOutermost());
        if (FPaths::GetExtension(filename).Equals(TEXT("json"))) {
            CurrentFilename = filename;
            if (Import(jsonAsset, CurrentFilename)) {
                result = EReimportResult::Succeeded;
                UE_LOG(LogTemp, Log, TEXT("UJsonAssetFactory::Reimport() - import file: %s"), *filename);
            } else {
                UE_LOG(LogTemp, Log, TEXT("UJsonAssetFactory::Reimport() - invalid json file: %s"), *filename);
            }
        } else {
            UE_LOG(LogTemp, Log, TEXT("UJsonAssetFactory::Reimport() - invalid json file: %s"), *filename);
        }
    } else {
        UE_LOG(LogTemp, Log, TEXT("UJsonAssetFactory::Reimport() - no object."));
    }
    return result;
}


