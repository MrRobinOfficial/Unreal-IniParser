// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IniData.h"
#include "IniProperty.h"
#include "IniSection.h"
#include "IniLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogIniParser, Log, All);

UCLASS()
class INIPARSER_API UIniLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * Parse .ini from a string
	 *
	 * @param IN String Only accept .ini style format. Read more about here: https://en.wikipedia.org/wiki/INI
	 * @return .ini data struct, populated from the string.
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary",
		meta = (DisplayName = "Parse .Ini From String")
	)
	static FIniData ParseIniFromString(FString String);

	/**
	 * Parse .Ini From File
	 *
	 * @param FilePath
	 * @return Lorem Ipsum
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary",
		meta = (DisplayName = "Parse .Ini From File")
	)
	static FIniData ParseIniFromFile(FString FilePath);

	/**
	 * Get section from .ini data
	 *
	 * @param Data
	 * @param SectionName
	 * @param OutSection
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetSection(UPARAM(ref) FIniData& Data, FName SectionName, FIniSection& OutSection);

	/**
	 * Tries to get section from .ini data
	 *
	 * @param Data
	 * @param SectionName
	 * @param OutSection
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static bool GetTrySection(UPARAM(ref) FIniData& Data, FName SectionName, FIniSection& OutSection);

	/**
	 * Get property from .ini data
	 *
	 * @param Data
	 * @param PropertyName
	 * @param OutProperty
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetProperty(UPARAM(ref) FIniSection& Section, FName PropertyName, FIniProperty& OutProperty);

	/**
	 * Tries to get property from .ini data
	 *
	 * @param Data
	 * @param PropertyName
	 * @param OutProperty
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static bool GetTryProperty(UPARAM(ref) FIniSection& Section, FName PropertyName, FIniProperty& OutProperty);

	/**
	 * Get property value as int32 type
	 *
	 * @param IN Property
	 * @param OUT Value
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsInt32(UPARAM(ref) FIniProperty& Property, int32& Value);

	/**
	 * Get property value as int64 type
	 *
	 * @param IN Property
	 * @param OUT Value
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsInt64(UPARAM(ref) FIniProperty& Property, int64& Value);

	/**
	 * Get property value as bool type
	 *
	 * @param IN Property
	 * @param OUT Value
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsBoolean(UPARAM(ref) FIniProperty& Property, bool& Value);


	/**
	 * Get property value as double type
	 *
	 * @param IN Property
	 * @param OUT Value
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsDouble(UPARAM(ref) FIniProperty& Property, double& Value);


	/**
	 * Get property value as float type
	 *
	 * @param IN Property
	 * @param OUT Value
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsFloat(UPARAM(ref) FIniProperty& Property, float& Value);

	/**
	 * Get property value as Vector type
	 *
	 * @param IN Property
	 * @param OUT Value
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsVector(UPARAM(ref) FIniProperty& Property, FVector& Value, bool& OutIsValid);

	/**
	 * Get property value as Vector3f type
	 *
	 * @param IN Property
	 * @param OUT Value
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsVector3f(UPARAM(ref) FIniProperty& Property, FVector3f& Value, bool& OutIsValid);

	/**
	 * Get property value as Vector2D type
	 *
	 * @param IN Property
	 * @param OUT Value
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsVector2D(UPARAM(ref) FIniProperty& Property, FVector2D& Value, bool& OutIsValid);

	/**
	 * Get property value as Rotator type
	 *
	 * @param IN Property
	 * @param OUT Value
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsRotator(UPARAM(ref) FIniProperty& Property, FRotator& Value, bool& OutIsValid);

	/**
	 * Get property value as Name type
	 *
	 * @param IN Property
	 * @param OUT Value
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsName(UPARAM(ref) FIniProperty& Property, FName& Value);

	/**
	 * Get property value as String type
	 *
	 * @param IN Property
	 * @param OUT Value
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsString(UPARAM(ref) FIniProperty& Property, FString& Value);

	/**
	 * Get property value as Text type
	 *
	 * @param IN Property
	 * @param OUT Value
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsText(UPARAM(ref) FIniProperty& Property, FText& Value);

	/**
	 * Get property value as LinearColor type
	 *
	 * @param IN Property
	 * @param OUT Value
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetValueAsLinearColor(UPARAM(ref) FIniProperty& Property, FLinearColor& Value, bool& OutIsValid);

	/**
	 * Get all sections from .ini data
	 *
	 * @param IN Data
	 * @param OUT OutArray
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetSections(UPARAM(ref) FIniData& Data, TArray<FIniSection>& OutArray);

	/**
	 * Get all properties from .ini section
	 *
	 * @param IN Section
	 * @param OUT OutArray
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetProperties(UPARAM(ref) FIniSection& Section, TArray<FIniProperty>& OutArray);

	/**
	 * Make .ini data struct via map of sections.
	 *
	 * @param IN Sections
	 * @return .ini data struct, populated with parameter sections.
	 */
	UFUNCTION(
		BlueprintPure,
		Category = "IniParser|IniLibrary",
		meta = (BlueprintThreadSafe)
	)
	static FIniData MakeIniDataStruct(TMap<FName, FIniSection> Sections);

	/**
	 * Convert .ini data into string
	 *
	 * @param IN Data
	 * @return Readable .ini data as a string format.
	 */
	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "IniParser|IniLibrary"
	)
	static FString Conv_IniDataToString(const FIniData& Data);

protected:
	/**
	 * Append character to buffer
	 *
	 * @param IN Buffer
	 * @param OUT Char
	 */
	static void AppendBuffer(char* Buffer, char Char);

	/**
	 * Trim the buffer (removes space and tab characters).
	 *
	 * @param IN Buffer
	 * @param OUT Value
	 */
	static void TrimBuffer(char* Buffer);
};
