// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "EditorReimportHandler.h"
#include "Assets/TextAsset.h"
#include "TextAssetFactory.generated.h"

/**
 * UTextAssetFactory
 */
UCLASS()
class BILLBOARDWALKER_API UTextAssetFactory : public UFactory, public FReimportHandler
{
    GENERATED_BODY()

    // コンストラクタ
public:
    UTextAssetFactory();

    // インポート
public:
    virtual UObject *FactoryCreateFile(UClass *InClass, UObject *InParent, FName InName, EObjectFlags Flags, const FString &Filename, const TCHAR *Parms, FFeedbackContext *Warn, bool & bOutOperationCanceled) override;
    bool Import(UTextAsset *asset, const FString &path);	

    // 再インポートハンドラ
protected:
    virtual bool CanReimport(UObject *Obj, TArray< FString > &OutFilenames) override;
    virtual void SetReimportPaths(UObject *Obj, const TArray< FString > &NewReimportPaths) override;
    virtual EReimportResult::Type Reimport(UObject *Obj) override;

};
