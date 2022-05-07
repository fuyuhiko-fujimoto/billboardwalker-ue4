// Fill out your copyright notice in the Description page of Project Settings.


#include "Walker.h"
#include "Engine/CollisionProfile.h"

// Sets default values
AWalker::AWalker()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // ルートの作成
    {
        root_ = CreateDefaultSubobject<UCapsuleComponent>(rootName_);
        if (root_ != nullptr) {
            root_->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
            root_->SetMobility(EComponentMobility::Movable);
            root_->SetGenerateOverlapEvents(false);
            root_->SetSimulatePhysics(true);
            root_->SetConstraintMode(EDOFMode::SixDOF);
            root_->GetBodyInstance()->bLockXRotation = true;
            root_->GetBodyInstance()->bLockYRotation = true;
            root_->InitCapsuleSize(rootRadius_, rootHeight_ * 0.5f);
            RootComponent = root_;
        }
    }

    // カメラの作成
    {
        camera_ = CreateDefaultSubobject<UCameraComponent>(cameraName_);
        if (camera_ != nullptr) {
            cameraArm_ = CreateDefaultSubobject<USpringArmComponent>(cameraArmName_);
            if (cameraArm_ != nullptr) {
                cameraArm_->SetupAttachment(RootComponent);
                /* 設定のサンプル
                cameraArm_->RelativeRotation = FRotator(-45.0f, 0.f, 0.f);
                cameraArm_->TargetArmLength = 400.0f;
                cameraArm_->bEnableCameraLag = true;
                cameraArm_->CameraLagSpeed = 3.0f;
                */
                camera_->SetupAttachment(cameraArm_, USpringArmComponent::SocketName);
            }
        }
    }

    // 移動の作成
    {
        movement_ = CreateDefaultSubobject<UWalkerMovementComponent>(movementName_);
        if (movement_ != nullptr) {
            movement_->UpdatedComponent = RootComponent;        
        }
    }
}

// Called when the game starts or when spawned
void AWalker::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void AWalker::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 向きの更新
    UpdateDirection();
}

// Called to bind functionality to input
void AWalker::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // 操作の割り当て
    if (AutoPossessPlayer != EAutoReceiveInput::Disabled) {
        BindInput(PlayerInputComponent);
    }
}

// UPawnMovementComponent を返す
UPawnMovementComponent *AWalker::GetMovementComponent() const
{
    return movement_;
}

// 操作を割り当てる
void AWalker::BindInput(UInputComponent *PlayerInputComponent)
{
    PlayerInputComponent->BindAxis("MoveForward", this, &AWalker::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AWalker::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &AWalker::Turn);
}

// 前進する
void AWalker::MoveForward(float axisValue)
{
    if (movement_ != nullptr && movement_->UpdatedComponent == RootComponent) {
        movement_->AddInputVector(GetActorForwardVector() * axisValue);
    }
}

// 右に移動する
void AWalker::MoveRight(float axisValue)
{
    if (movement_ != nullptr && movement_->UpdatedComponent == RootComponent) {
        movement_->AddInputVector(GetActorRightVector() * axisValue);
    }
}

// 方向を変える
void AWalker::Turn(float axisValue)
{
    if (movement_ != nullptr && movement_->UpdatedComponent == RootComponent) {
        FRotator rotation = GetActorRotation();
        rotation.Yaw += axisValue;
        SetActorRotation(rotation);
    }
}

// 向きを更新する
void AWalker::UpdateDirection()
{
    if (movement_ != nullptr) {
        FVector v0 = movement_->GetMoveVector();
        if (!v0.IsNearlyZero()) {
            FVector v1 = GetActorForwardVector();
            v0.Z = 0.0f;
            v1.Z = 0.0f;
            float angle = FMath::Acos(FVector::DotProduct(v0, v1) / (v0.Size() * v1.Size()));
            if (angle <= PI * 0.3f) {
                direction_ = EWalkerDirection::Forward;
            } else if (angle >= PI * 0.7f) {
                direction_ = EWalkerDirection::Back;
            } else {
                float cross = v1.X * v0.Y - v1.Y * v0.X;
                if (cross <= 0.0f) {
                    direction_ = EWalkerDirection::Left;
                } else {
                    direction_ = EWalkerDirection::Right;
                }
            }
        }
    }
}

