// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "INILibrary.generated.h"

UCLASS()
class INIPARSER_API UINILibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(
		BlueprintCallable,
		Category = "Libraries|INILibrary",
		meta = (DisplayName = "Load .Ini File")
	)
	static TArray<FString> LoadINIFile(FString FilePath);

	UFUNCTION(
		BlueprintCallable,
		Category = "Libraries|INILibrary",
		meta = (DisplayName = "Try Load .Ini File")
	)
	static bool TryLoadINIFile(FString FilePath, TArray<FString>& OutContents);

	UFUNCTION(
		BlueprintCallable,
		Category = "Libraries|INILibrary",
		meta = (DisplayName = "Write .Ini File")
	)
	static void WriteINIFile(FString FilePath, TArray<FString> Contents);

	UFUNCTION(
		BlueprintCallable,
		Category = "Libraries|INILibrary",
		meta = (DisplayName = "Try Write .Ini File")
	)
	static bool TryWriteINIFile(FString FilePath, TArray<FString> Contents);

	UFUNCTION(
		BlueprintCallable,
		Category = "Libraries|INILibrary",
		meta = (DisplayName = "Parse .Ini File")
	)
	static TArray<FString> ParseINIFile(FString Data);

	UFUNCTION(
		BlueprintCallable,
		Category = "Libraries|INILibrary",
		meta = (DisplayName = "Try Parse .Ini File")
	)
	static bool TryParseINIFile(FString Data, TArray<FString>& OutContents);

protected:
	static void AppendBuffer(char* Buffer, const char Char);
	static void TrimBuffer(char* Buffer);
};
