// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Characters/WalkerMovementComponent.h"
#include "Walker.generated.h"

/**
 * EWalkerDirection
 */
UENUM(BlueprintType)
enum class EWalkerDirection : uint8 {
    Back = 0, 
    Forward, 
    Left, 
    Right, 
    Length, 
};

/**
 * AWalker
 */
UCLASS()
class BILLBOARDWALKER_API AWalker : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    AWalker();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    // ルート
protected:
    UPROPERTY(EditAnywhere, Category = "Root")
    UCapsuleComponent *root_;
    FName rootName_ = FName(TEXT("Root"));
    UPROPERTY(EditAnywhere, Category = "Root")
    float rootHeight_ = 170.0f;
    UPROPERTY(EditAnywhere, Category = "Root")
    float rootRadius_ = 42.5f;

    // カメラ
protected:
    UPROPERTY(EditAnywhere, Category = "Camera")
    UCameraComponent *camera_;
    FName cameraName_ = FName(TEXT("Camera"));
    UPROPERTY(EditAnywhere, Category = "Camera")
    USpringArmComponent *cameraArm_;
    FName cameraArmName_ = FName(TEXT("CameraArm"));

    // 移動
protected:
    UPROPERTY(EditAnywhere, Category = "Movement")
    UWalkerMovementComponent *movement_;
    FName movementName_ = FName(TEXT("Movement"));
protected:
    virtual UPawnMovementComponent *GetMovementComponent() const override;
    void BindInput(UInputComponent *PlayerInputComponent);
    void MoveForward(float axisValue);
    void MoveRight(float axisValue);
    void Turn(float axisValue);

    // 向き
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Direction")
    EWalkerDirection direction_;
protected:
    void UpdateDirection();

};
