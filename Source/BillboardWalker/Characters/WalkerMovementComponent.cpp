// Fill out your copyright notice in the Description page of Project Settings.


#include "WalkerMovementComponent.h"


// Tick 毎の処理を行う
void UWalkerMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    // Super
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Tick の更新
    if (PawnOwner != nullptr && UpdatedComponent != nullptr && !ShouldSkipUpdate(DeltaTime)) {

        // 移動量の取得
        FVector vector = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * moveSpeed_;
        if (!vector.IsNearlyZero()) {

            // 移動
            FHitResult Hit;
            SafeMoveUpdatedComponent(vector, UpdatedComponent->GetComponentRotation(), true, Hit);

            // コリジョンにヒットしたときに沿わせる
            if (Hit.IsValidBlockingHit()) {
                SlideAlongSurface(vector, 1.0f - Hit.Time, Hit.Normal, Hit);
            }
        }

        // 移動量の保持
        moveVector_ = vector;
    }
}

// 移動量を取得する
FVector &UWalkerMovementComponent::GetMoveVector()
{
    return moveVector_;
}
    
