// Fill out your copyright notice in the Description page of Project Settings.


#include "TextAssetFactory.h"
#include "Misc/FileHelper.h"
#include "EditorFramework/AssetImportData.h"


// コンストラクタ
UTextAssetFactory::UTextAssetFactory()
    : UFactory(), FReimportHandler()
{
    Formats.Add(FString(TEXT("txt;")) + NSLOCTEXT("UTextAssetFactory", "FormatText", "Text").ToString());
    SupportedClass = UTextAsset::StaticClass();
    bCreateNew = false;
    bEditorImport = true;
}

// ファイルをインポートしてクラスオブジェクトを作成する
UObject *UTextAssetFactory::FactoryCreateFile(UClass *InClass, UObject *InParent, FName InName, EObjectFlags Flags, const FString &Filename, const TCHAR *Parms, FFeedbackContext *Warn, bool & bOutOperationCanceled)
{
    UTextAsset *textAsset = NewObject<UTextAsset>(InParent, InClass, InName, Flags);
    if (textAsset != nullptr) {
        if (Import(textAsset, Filename)) {
            UE_LOG(LogTemp, Log, TEXT("UTextAssetFactory::FactoryCreateFile() - import file: %s"), *Filename);
        } else {
            UE_LOG(LogTemp, Log, TEXT("UTextAssetFactory::FactoryCreateFile() - invalid text file: %s"), *Filename);
        }
    } else {
        UE_LOG(LogTemp, Log, TEXT("UTextAssetFactory::FactoryCreateFile() - no object."));
    }
    bOutOperationCanceled = false;
    return textAsset;
}

// ファイルからアセットをインポートする
bool UTextAssetFactory::Import(UTextAsset *asset, const FString &path)
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
bool UTextAssetFactory::CanReimport(UObject *Obj, TArray<FString> &OutFilenames)
{
    bool result = false;
    UTextAsset *textAsset = Cast<UTextAsset>(Obj);
    if (textAsset != nullptr) {
        OutFilenames.Add(UAssetImportData::ResolveImportFilename(textAsset->GetSourcePath(), textAsset->GetOutermost()));
        result = true;
        UE_LOG(LogTemp, Log, TEXT("UTextAssetFactory::CanReimport() - check file: %s"), *textAsset->GetSourcePath());
    } else {
        UE_LOG(LogTemp, Log, TEXT("UTextAssetFactory::CanReimport() - no object."));
    }
    return result;
}

// 再インポートするパスを設定する
void UTextAssetFactory::SetReimportPaths(UObject *Obj, const TArray< FString > & NewReimportPaths)
{
    UTextAsset *textAsset = Cast<UTextAsset>(Obj);
    if (textAsset != nullptr && ensure(NewReimportPaths.Num() == 1)) {
        textAsset->SetSourcePath(UAssetImportData::SanitizeImportFilename(NewReimportPaths[0], textAsset->GetOutermost()));
        UE_LOG(LogTemp, Log, TEXT("UTextAssetFactory::SetReimportPaths() - import file: %s"), *textAsset->GetSourcePath());
    } else {
        UE_LOG(LogTemp, Log, TEXT("UTextAssetFactory::SetReimportPaths() - no object."));
    }
}

// 再インポートする
EReimportResult::Type UTextAssetFactory::Reimport(UObject *Obj)
{
    EReimportResult::Type result = EReimportResult::Failed;
    UTextAsset *textAsset = Cast<UTextAsset>(Obj);
    if (textAsset != nullptr) {
        const FString filename = UAssetImportData::ResolveImportFilename(textAsset->GetSourcePath(), textAsset->GetOutermost());
        if (FPaths::GetExtension(filename).Equals(TEXT("txt"))) {
            CurrentFilename = filename;
            if (Import(textAsset, CurrentFilename)) {
                result = EReimportResult::Succeeded;
                UE_LOG(LogTemp, Log, TEXT("UTextAssetFactory::Reimport() - import file: %s"), *filename);
            } else {
                UE_LOG(LogTemp, Log, TEXT("UTextAssetFactory::Reimport() - invalid text file: %s"), *filename);
            }
        } else {
            UE_LOG(LogTemp, Log, TEXT("UTextAssetFactory::Reimport() - invalid text file: %s"), *filename);
        }
    } else {
        UE_LOG(LogTemp, Log, TEXT("UTextAssetFactory::Reimport() - no object."));
    }
    return result;
}


