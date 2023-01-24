// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IniData.h"
#include "IniProperty.h"
#include "IniSection.h"
#include "IniLibrary.generated.h"

UCLASS()
class INIPARSER_API UIniLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary",
		meta = (DisplayName = "Parse .Ini String")
	)
	static FIniData ParseIniString(FString String);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetSection(UPARAM(ref) FIniData& Data, FString SectionName, FIniSection& OutSection);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static bool GetTrySection(UPARAM(ref) FIniData& Data, FString SectionName, FIniSection& OutSection);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetProperty(UPARAM(ref) FIniSection& Section, FString PropertyName, FIniProperty& OutProperty);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static bool GetTryProperty(UPARAM(ref) FIniSection& Section, FString PropertyName, FIniProperty& OutProperty);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsInt32(UPARAM(ref) FIniProperty& Property, int32& Value);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsInt64(UPARAM(ref) FIniProperty& Property, int64& Value);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsBoolean(UPARAM(ref) FIniProperty& Property, bool& Value);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsDouble(UPARAM(ref) FIniProperty& Property, double& Value);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsFloat(UPARAM(ref) FIniProperty& Property, float& Value);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsVector(UPARAM(ref) FIniProperty& Property, FVector& Value, bool& OutIsValid);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsVector3f(UPARAM(ref) FIniProperty& Property, FVector3f& Value, bool& OutIsValid);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsVector2D(UPARAM(ref) FIniProperty& Property, FVector2D& Value, bool& OutIsValid);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsRotator(UPARAM(ref) FIniProperty& Property, FRotator& Value, bool& OutIsValid);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsName(UPARAM(ref) FIniProperty& Property, FName& Value);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsString(UPARAM(ref) FIniProperty& Property, FString& Value);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsText(UPARAM(ref) FIniProperty& Property, FText& Value);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsLinearColor(UPARAM(ref) FIniProperty& Property, FLinearColor& Value, bool& OutIsValid);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetSections(UPARAM(ref) FIniData& Data, TArray<FIniSection>& OutArray);

	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetProperties(UPARAM(ref) FIniSection& Section, TArray<FIniProperty>& OutArray);

	UFUNCTION(
		BlueprintPure,
		Category = "IniParser|IniLibrary",
		meta = (BlueprintThreadSafe)
	)
	static FIniData MakeIniDataStruct(TMap<FString, FIniSection> Sections);

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "IniParser|IniLibrary"
	)
	static FString Conv_IniDataToString(const FIniData& Data);

protected:
	static void AppendBuffer(char* Buffer, char Char);
	static void TrimBuffer(char* Buffer);
};
