// Fill out your copyright notice in the Description page of Project Settings.


#include "Tilemap.h"
#include "Engine/World.h"
#include "Environments/Tileset.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

// Sets default values
ATilemap::ATilemap()
{
     // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // ルートコンポーネントの作成
    {
        USceneComponent *scene = CreateDefaultSubobject<USceneComponent>(rootName_);
        if (scene != nullptr) {
            RootComponent = scene;
        }
    }

}

// Called when the game starts or when spawned
void ATilemap::BeginPlay()
{
    Super::BeginPlay();

    // マップの読み込み
    LoadMap();

    // ビューの配置
    LayoutPlayerStart();
}

// Called whenever this actor is being removed from a level
void ATilemap::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // レイアウトの破棄
    Unlayout();
}

// Called every frame
void ATilemap::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // レイアウトの更新
    LayoutPlayerTranslation();
}

// マップを読み込む
void ATilemap::LoadMap()
{
    // Json の取得
    TSharedPtr<FJsonObject> jsonObject = mapJsonAsset_->GetJsonObject();
    if (jsonObject != nullptr) {

        // "layers" フィールドの取得
        const TArray<TSharedPtr<FJsonValue>> *layers;
        if (jsonObject->TryGetArrayField(TEXT("layers"), layers)) {
            const TSharedPtr<FJsonObject> layerObject = layers->GetData()[0]->AsObject();
            if (layerObject != nullptr) {

                // "data" フィールドの取得
                const TArray<TSharedPtr<FJsonValue>> *data;
                if (layerObject->TryGetArrayField(TEXT("data"), data)) {

                    // マップの大きさの取得
                    mapSize_.X = layerObject->GetIntegerField(TEXT("width"));
                    mapSize_.Y = layerObject->GetIntegerField(TEXT("height"));
                    if (mapSize_.X * mapSize_.Y <= data->Num()) {

                        // マップデータの読み込み
                        mapDatas_.Init(0, data->Num());
                        for (int32 i = 0; i < data->Num(); i++) {
                            mapDatas_[i] = data->GetData()[i]->AsNumber() - 1;
                        }

                        // タイルセットの初期化
                        // layoutTilesets_.Init(nullptr, data->Num());
                    }
                }
            }
        }
    }
}

//プレイヤの開始位置にタイルセットを配置する
void ATilemap::LayoutPlayerStart()
{
    // プレイヤスタートの取得
    TArray<AActor *> starts;
    UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), starts);
    for (AActor *start : starts) {
        if (start->AutoReceiveInput == layoutPlayer_) {

            // マップの存在
            if (mapDatas_.Num() > 0) {

                // タイルセットの初期化
                layoutTilesets_.Init(nullptr, mapDatas_.Num());

                // 中心の取得
                FVector translation = start->GetTransform().GetTranslation();
                FIntPoint center = FIntPoint(
                    FMath::FloorToInt(translation.X / tilesetSize_.X), 
                    FMath::FloorToInt(translation.Y / tilesetSize_.Y)
                );
                FIntRect rect = FIntRect(
                    FMath::Max(center.X - layoutRange_, 0), 
                    FMath::Max(center.Y - layoutRange_, 0), 
                    FMath::Min(center.X + layoutRange_ + 1, mapSize_.X), 
                    FMath::Min(center.Y + layoutRange_ + 1, mapSize_.Y)
                );

                // タイルセットの配置
                for (int32 y = rect.Min.Y; y < rect.Max.Y; y++) {
                    for (int32 x = rect.Min.X; x < rect.Max.X; x++) {
                        LayoutTileset(x, y);
                    }
                }

                // 中心の更新
                layoutCenter_ = center;
            }
        }
    }
}

// プレイヤの位置に合わせてタイルセットを配置する
void ATilemap::LayoutPlayerTranslation()
{
    // プレイヤの取得
    APawn *pawn = UGameplayStatics::GetPlayerPawn(this, layoutPlayer_ - EAutoReceiveInput::Type::Player0);
    if (pawn != nullptr) {

        // 中心の移動
        FVector translation = pawn->GetTransform().GetTranslation();
        FIntPoint center = FIntPoint(
            FMath::FloorToInt(translation.X / tilesetSize_.X), 
            FMath::FloorToInt(translation.Y / tilesetSize_.Y)
        );
        if (layoutCenter_ != center) {

            // 矩形の取得
            FIntRect r0 = FIntRect(
                FMath::Max(layoutCenter_.X - layoutRange_, 0), 
                FMath::Max(layoutCenter_.Y - layoutRange_, 0), 
                FMath::Min(layoutCenter_.X + layoutRange_ + 1, mapSize_.X), 
                FMath::Min(layoutCenter_.Y + layoutRange_ + 1, mapSize_.Y)
            );
            FIntRect r1 = FIntRect(
                FMath::Max(center.X - layoutRange_, 0), 
                FMath::Max(center.Y - layoutRange_, 0), 
                FMath::Min(center.X + layoutRange_ + 1, mapSize_.X), 
                FMath::Min(center.Y + layoutRange_ + 1, mapSize_.Y)
            );

            // タイルセットの破棄
            for (int32 y = r0.Min.Y; y < r0.Max.Y; y++) {
                for (int32 x = r0.Min.X; x < r0.Max.X; x++) {
                    if (!r1.Contains(FIntPoint(x, y))) {
                        UnlayoutTileset(x, y);
                    }
                }
            }

            // タイルセットの生成
            for (int32 y = r1.Min.Y; y < r1.Max.Y; y++) {
                for (int32 x = r1.Min.X; x < r1.Max.X; x++) {
                    if (!r0.Contains(FIntPoint(x, y))) {
                        LayoutTileset(x, y);
                    }
                }
            }

            // 中心の更新
            layoutCenter_ = center;
        }
    }
}

// 指定された位置にタイルセットを配置する
void ATilemap::LayoutTileset(int32 x, int32 y)
{
    if (0 <= x && x < mapSize_.X && 0 <= y && y < mapSize_.Y) {
        if (layoutTilesets_[y * mapSize_.X + x] == nullptr) {
            int32 name = mapDatas_[y * mapSize_.X + x];
            int32 edge = 0;
            if (name >= static_cast<int32>(ETilesetName::Length)) {
                name = static_cast<int32>(ETilesetName::Null);
            } else if (name == static_cast<int32>(ETilesetName::Water)) {
                if (y > 0 && mapDatas_[(y - 1) * mapSize_.X + x] != static_cast<int32>(ETilesetName::Water)) {
                    edge |= 0x01;
                }
                if (y < mapSize_.Y - 1 && mapDatas_[(y + 1) * mapSize_.X + x] != static_cast<int32>(ETilesetName::Water)) {
                    edge |= 0x02;
                }
                if (x > 0 && mapDatas_[y * mapSize_.X + (x - 1)] != static_cast<int32>(ETilesetName::Water)) {
                    edge |= 0x04;
                }
                if (x < mapSize_.X - 1 && mapDatas_[y * mapSize_.X + (x + 1)] != static_cast<int32>(ETilesetName::Water)) {
                    edge |= 0x08;
                }
            }
            ATileset *tileset = GetWorld()->SpawnActor<ATileset>(tilesetClasses_[name]);
            if (tileset != nullptr) {
                tileset->SetActorLocation(FVector(
                    (x * tilesetSize_.X) + (tilesetSize_.X / 2.0f), 
                    (y * tilesetSize_.Y) + (tilesetSize_.Y / 2.0f), 
                    0.0f
                ));
                tileset->SetParameter(edge);
                tileset->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
                layoutTilesets_[y * mapSize_.X + x] = tileset;
            }
        }
    }
}

// 配置されたレイアウトを破棄する
void ATilemap::Unlayout()
{
    layoutTilesets_.Empty();
}

// 指定された位置のタイルセットを破棄する
void ATilemap::UnlayoutTileset(int32 x, int32 y)
{
    if (0 <= x && x < mapSize_.X && 0 <= y && y < mapSize_.Y) {
        ATileset *tileset = layoutTilesets_[y * mapSize_.X + x];
        if (tileset != nullptr) {
            tileset->Destroy();
            layoutTilesets_[y * mapSize_.X + x] = nullptr;
        }
    }
}
