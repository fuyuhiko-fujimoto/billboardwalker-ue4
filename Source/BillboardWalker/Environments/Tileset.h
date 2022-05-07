// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tileset.generated.h"

/**
 * ETilesetName
 */
UENUM(BlueprintType)
enum class ETilesetName : uint8 {
    Null = 0, 
    Water, 
    Glassland, 
    Desert, 
    Swamp, 
    Bridge, 
    Tree, 
    Hill, 
    Mountain, 
    Stone, 
    Cave, 
    Stairs, 
    Town, 
    Castle, 
    Length, 
};

/**
 * ATileset
 */
UCLASS()
class BILLBOARDWALKER_API ATileset : public AActor
{
    GENERATED_BODY()
    
public:	
    // Sets default values for this actor's properties
    ATileset();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // パラメータ
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameter")
    int32 parameter_ = 0;
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Parameter")
    void SetParameter(int32 parameter);
    virtual void SetParameter_Implementation(int32 parameter);

};
