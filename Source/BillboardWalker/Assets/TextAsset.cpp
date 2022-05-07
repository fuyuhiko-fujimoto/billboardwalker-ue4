// Fill out your copyright notice in the Description page of Project Settings.


#include "TextAsset.h"


// ソースファイルのパスを取得する
FString &UTextAsset::GetSourcePath()
{
    return sourcePath_;
}

// ソースファイルのパスを設定する
void UTextAsset::SetSourcePath(const FString &path)
{
    sourcePath_ = path;
}

// 文字列を取得する
FString UTextAsset::GetString()
{
    return string_;
}

// 文字列を設定する
bool UTextAsset::SetString(const FString &string)
{
    string_ = string;
    return true;
}

