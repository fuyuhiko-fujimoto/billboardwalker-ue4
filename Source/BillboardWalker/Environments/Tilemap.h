// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Assets/JsonAsset.h"
#include "Environments/Tileset.h"
#include "Tilemap.generated.h"

/**
 * ATilemap
 */
UCLASS()
class BILLBOARDWALKER_API ATilemap : public AActor
{
    GENERATED_BODY()

public:	
    // Sets default values for this actor's properties
    ATilemap();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

protected:
    // Called whenever this actor is being removed from a level
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // ルート
protected:
    FName rootName_ = FName(TEXT("Root"));

    // タイルセット
protected:
    UPROPERTY(EditAnywhere, Category = "Tileset")
    TArray<TSubclassOf<ATileset>> tilesetClasses_;
    const FVector tilesetSize_ = FVector(200.0f, 200.0f, 25.0f);

    // マップ
protected:
    UPROPERTY(EditAnywhere, Category = "Map")
    UJsonAsset *mapJsonAsset_ = nullptr;
    FIntVector mapSize_ = FIntVector(0);
    TArray<int32> mapDatas_;
protected:
    void LoadMap();

    // レイアウト
protected:
    UPROPERTY(EditAnywhere, Category = "Layout")
    TEnumAsByte<EAutoReceiveInput::Type> layoutPlayer_ = EAutoReceiveInput::Type::Player0;
    UPROPERTY(EditAnywhere, Category = "Layout")
    int32 layoutRange_ = 8;
    FIntPoint layoutCenter_;
    TArray<ATileset *> layoutTilesets_;
protected:
    void LayoutPlayerStart();
    void LayoutPlayerTranslation();
    void LayoutTileset(int32 x, int32 y);
    void Unlayout();
    void UnlayoutTileset(int32 x, int32 y);

};
