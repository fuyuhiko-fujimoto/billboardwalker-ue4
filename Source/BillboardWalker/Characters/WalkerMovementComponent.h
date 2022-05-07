// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "WalkerMovementComponent.generated.h"

/**
 * UWalkerMovementComponent
 */
UCLASS()
class BILLBOARDWALKER_API UWalkerMovementComponent : public UPawnMovementComponent
{
    GENERATED_BODY()

    // Tick 毎の処理
private:
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
    
    // 移動
protected:
    UPROPERTY(EditAnywhere, Category = "Move")
    float moveSpeed_ = 200.0f;
    FVector moveVector_ = FVector(0.0f);
public:
    FVector &GetMoveVector();

};
