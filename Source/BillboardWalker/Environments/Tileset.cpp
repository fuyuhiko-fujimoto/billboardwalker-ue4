// Fill out your copyright notice in the Description page of Project Settings.


#include "Tileset.h"

// Sets default values
ATileset::ATileset()
{
     // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATileset::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ATileset::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

// パラメータを設定する
void ATileset::SetParameter_Implementation(int32 parameter)
{
    parameter_ = parameter;
}
