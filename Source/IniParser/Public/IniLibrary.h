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
	/**
	 * Parse .ini from a string
	 *
	 * @param String Only accept .ini style format. Read more about here: https://en.wikipedia.org/wiki/INI
	 * @return .ini data, populated from the string.
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary",
		meta = (DisplayName = "Parse .Ini From String")
	)
	static FIniData ParseIniFromString(FString String);

	/**
	 * .ini to a string
	 *
	 * @param Data
	 * @return A string populated from the .ini data.
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary",
		meta = (DisplayName = "Parse .Ini To String")
	)
	static FString ParseIniToString(const FIniData& Data);

	/**
	 * Read .Ini From File
	 *
	 * @param FilePath
	 * @return A new instance of ini data
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary",
		meta = (DisplayName = "Parse .Ini From File")
	)
	static FIniData ReadIniFromFile(FString FilePath);

	/**
	 * Write .Ini From File
	 *
	 * @param FilePath
	 * @param Data
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary",
		meta = (DisplayName = "Write .Ini To File")
	)
	static void WriteIniToFile(FString FilePath, const FIniData& Data);

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
	static void GetProperties(UPARAM(ref) FIniData& Data, FName SectionName, TArray<FIniProperty>& OutArray);

	/**
	 * Get all comments from .ini section
	 *
	 * @param IN Data
	 * @param OUT OutArray
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetComments(UPARAM(ref) FIniData& Data, FName SectionName, TArray<FString>& OutArray);

	/**
	 * Get global properties from .ini data
	 *
	 * @param IN Section
	 * @param OUT OutArray
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalProperties(UPARAM(ref) FIniData& Data, TArray<FIniProperty>& OutArray);

	/**
	 * Get global comments from .ini data
	 *
	 * @param IN Section
	 * @param OUT OutArray
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalComments(UPARAM(ref) FIniData& Data, TArray<FString>& OutArray);

	/**
	 * Make .ini data via map of sections.
	 *
	 * @param IN Sections
	 * @return .ini data, populated with parameter sections.
	 */
	UFUNCTION(
		BlueprintPure,
		Category = "IniParser|IniLibrary",
		meta = (BlueprintThreadSafe)
	)
	static FIniData MakeIniData(TMap<FName, FIniSection> Sections);

	/**
	 * Make .ini data via map of sections.
	 *
	 * @param IN Sections
	 * @return .ini data, populated with parameter sections.
	 */
	UFUNCTION(
		BlueprintPure,
		Category = "IniParser|IniLibrary",
		meta = (BlueprintThreadSafe)
	)
	static FIniSection MakeIniSection(TMap<FName, FIniProperty> Properties);

	/**
	 * Convert .ini data into string
	 *
	 * @param IN Data
	 * @return A string
	 */
	UFUNCTION(
		BlueprintPure,
		Category = "IniParser|IniLibrary",
		meta = (DisplayName = "To String",
		CompactNodeTitle = "->", BlueprintAutocast))
	static FString Conv_IniDataToString(const FIniData& Data);

public:
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
	static void GetIniPropertyValueAsInt(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, int32& OutValue);

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
	static void GetIniPropertyValueAsInt64(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, int64& OutValue);

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
	static void GetIniPropertyValueAsBoolean(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, bool& OutValue);

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
	static void GetIniPropertyValueAsFloat(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, float& OutValue);

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
	static void GetIniPropertyValueAsDouble(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, double& OutValue);


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
	static void GetIniPropertyValueAsVector(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FVector& OutConvertedVector, bool& OutIsValid);

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
	static void GetIniPropertyValueAsVector3f(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FVector3f& OutConvertedVector, bool& OutIsValid);

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
	static void GetIniPropertyValueAsVector2D(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FVector2D& OutConvertedVector2D, bool& OutIsValid);

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
	static void GetIniPropertyValueAsRotator(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FRotator& OutConvertedRotator, bool& OutIsValid);

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
	static void GetIniPropertyValueAsLinearColor(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FLinearColor& OutConvertedColor, bool& OutIsValid);

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
	static void GetIniPropertyValueAsName(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FName& Value);

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
	static void GetIniPropertyValueAsText(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FText& Value);

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
	static void GetIniPropertyValueAsString(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FString& Value);

public:
	/**
	 * Set property value as String type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsString(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FString NewValue);

	/**
	 * Set property value as Text type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsText(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FText NewValue);

	/**
	 * Set property value as Name type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsName(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FName NewValue);

	/**
	 * Set property value as Object type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsObject(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, UObject* NewValue);

	/**
	 * Set property value as uint8 type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsByte(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, uint8 NewValue);

	/**
	 * Set property value as int32 type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsInt(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, int32 NewValue);

	/**
	 * Set property value as int64 type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsInt64(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, int64 NewValue);

	/**
	 * Set property value as IntPoint type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsIntPoint(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FIntPoint NewValue);

	/**
	 * Set property value as boolean type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsBool(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, bool bNewValue);

	/**
	 * Set property value as float type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsFloat(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, float NewValue);

	/**
	 * Set property value as double type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsDouble(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, double NewValue);

	/**
	 * Set property value as Vector type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsVector(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FVector NewValue);

	/**
	 * Set property value as Vector2D type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsVector2D(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FVector2D NewValue);

	/**
	 * Set property value as Vector3f type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsVector3f(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FVector3f NewValue);

	/**
	 * Set property value as IntVector type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsIntVector(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FIntVector NewValue);

	/**
	 * Set property value as Rotator type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsRotator(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FRotator NewValue);

	/**
	 * Set property value as Matrix type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsMatrix(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FMatrix NewValue);

	/**
	 * Set property value as Transform type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsTransform(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FTransform NewValue);

	/**
	 * Set property value as LinearColor type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsLinearColor(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FLinearColor NewValue);

	/**
	 * Set property value as InputDeviceId type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsInputDeviceId(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FInputDeviceId NewValue);

	/**
	 * Set property value as PlatformUserId type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetIniPropertyValueAsPlatformUserId(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FPlatformUserId NewValue);

private:
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
