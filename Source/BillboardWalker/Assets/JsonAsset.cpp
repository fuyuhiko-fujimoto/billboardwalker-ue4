// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonAsset.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"


// ソースファイルのパスを取得する
FString &UJsonAsset::GetSourcePath()
{
    return sourcePath_;
}

// ソースファイルのパスを設定する
void UJsonAsset::SetSourcePath(const FString &path)
{
    sourcePath_ = path;
}

// 文字列を取得する
FString &UJsonAsset::GetString()
{
    return string_;
}

// 文字列を設定する
bool UJsonAsset::SetString(const FString &string)
{
    string_ = string;
    return true;
}

// Json オブジェクトを取得する
TSharedPtr<FJsonObject> UJsonAsset::GetJsonObject()
{
    TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
    if (jsonObject != nullptr) {
        TSharedRef<TJsonReader<TCHAR>> jsonReader = TJsonReaderFactory<TCHAR>::Create(string_);
        FJsonSerializer::Deserialize(jsonReader, jsonObject);
    }
    return jsonObject;
}

