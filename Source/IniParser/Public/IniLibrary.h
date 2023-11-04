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
	 * Get number of sections from .ini data
	 *
	 * @param IN Data
	 * @return A number of sections
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static int32 GetNumOfSections(UPARAM(ref) FIniData& Data);

	/**
	 * Get number of global comments from .ini data
	 *
	 * @param IN Data
	 * @return A number of global comments
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static int32 GetNumOfGlobalComments(UPARAM(ref) FIniData& Data);

	/**
	 * Get number of global properties from .ini data
	 *
	 * @param IN Data
	 * @return A number of global properties
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static int32 GetNumOfGlobalProperties(UPARAM(ref) FIniData& Data);

	/**
	 * Get number of properties from .ini section
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @return A number of properties
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static int32 GetNumOfProperties(UPARAM(ref) FIniData& Data, FName SectionName);

	/**
	 * Get number of comments from .ini section
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @return A number of comments
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static int32 GetNumOfComments(UPARAM(ref) FIniData& Data, FName SectionName);

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
	 * Get global property value as Name type
	 *
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalPropertyValueAsName(UPARAM(ref) FIniData& Data, FName PropertyName, FName& OutValue);

	/**
	 * Get global property value as Text type
	 *
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalPropertyValueAsText(UPARAM(ref) FIniData& Data, FName PropertyName, FText& OutValue);

	/**
	 * Get global property value as String type
	 *
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalPropertyValueAsString(UPARAM(ref) FIniData& Data, FName PropertyName, FString& OutValue);

	/**
	 * Get global property value as int32 type
	 *
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalPropertyValueAsInt(UPARAM(ref) FIniData& Data, FName PropertyName, int32& OutValue);

	/**
	 * Get global property value as int64 type
	 *
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalPropertyValueAsInt64(UPARAM(ref) FIniData& Data, FName PropertyName, int64& OutValue);

	/**
	 * Get global property value as bool type
	 *
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalPropertyValueAsBoolean(UPARAM(ref) FIniData& Data, FName PropertyName, bool& OutValue);

	/**
	 * Get global property value as float type
	 *
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalPropertyValueAsFloat(UPARAM(ref) FIniData& Data, FName PropertyName, float& OutValue);

	/**
	 * Get global property value as double type
	 *
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalPropertyValueAsDouble(UPARAM(ref) FIniData& Data, FName PropertyName, double& OutValue);

	/**
	 * Get global property value as Vector type
	 *
	 * @param IN OutConvertedVector
	 * @param OUT OutIsValid
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalPropertyValueAsVector(UPARAM(ref) FIniData& Data, FName PropertyName, FVector& OutConvertedVector, bool& OutIsValid);

	/**
	 * Get global property value as Vector3f type
	 *
	 * @param IN OutConvertedVector
	 * @param OUT OutIsValid
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalPropertyValueAsVector3f(UPARAM(ref) FIniData& Data, FName PropertyName, FVector3f& OutConvertedVector, bool& OutIsValid);

	/**
	 * Get global property value as Vector2D type
	 *
	 * @param IN OutConvertedVector2D
	 * @param OUT OutIsValid
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalPropertyValueAsVector2D(UPARAM(ref) FIniData& Data, FName PropertyName, FVector2D& OutConvertedVector2D, bool& OutIsValid);

	/**
	 * Get global property value as Rotator type
	 *
	 * @param IN OutConvertedRotator
	 * @param OUT OutIsValid
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalPropertyValueAsRotator(UPARAM(ref) FIniData& Data, FName PropertyName, FRotator& OutConvertedRotator, bool& OutIsValid);

	/**
	 * Get global property value as LinearColor type
	 *
	 * @param IN OutConvertedColor
	 * @param OUT OutIsValid
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetGlobalPropertyValueAsLinearColor(UPARAM(ref) FIniData& Data, FName PropertyName, FLinearColor& OutConvertedColor, bool& OutIsValid);

public:
	/**
	 * Set global property value as Name type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsName(UPARAM(ref) FIniData& Data, FName PropertyName, FName NewValue);

	/**
	 * Set global property value as Text type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsText(UPARAM(ref) FIniData& Data, FName PropertyName, FText NewValue);

	/**
	 * Set global property value as String type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsString(UPARAM(ref) FIniData& Data, FName PropertyName, FString NewValue);

	/**
	 * Set global property value as Object type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsObject(UPARAM(ref) FIniData& Data, FName PropertyName, UObject* NewValue);

	/**
	 * Set global property value as uint8 type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsByte(UPARAM(ref) FIniData& Data, FName PropertyName, uint8 NewValue);

	/**
	 * Set global property value as int32 type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsInt(UPARAM(ref) FIniData& Data, FName PropertyName, int32 NewValue);

	/**
	 * Set global property value as int64 type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsInt64(UPARAM(ref) FIniData& Data, FName PropertyName, int64 NewValue);

	/**
	 * Set global property value as IntPoint type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsIntPoint(UPARAM(ref) FIniData& Data, FName PropertyName, FIntPoint NewValue);

	/**
	 * Set global property value as boolean type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsBool(UPARAM(ref) FIniData& Data, FName PropertyName, bool bNewValue);

	/**
	 * Set global property value as float type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsFloat(UPARAM(ref) FIniData& Data, FName PropertyName, float NewValue);

	/**
	 * Set global property value as double type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsDouble(UPARAM(ref) FIniData& Data, FName PropertyName, double NewValue);

	/**
	 * Set global property value as Vector type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsVector(UPARAM(ref) FIniData& Data, FName PropertyName, FVector NewValue);

	/**
	 * Set global property value as Vector2D type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsVector2D(UPARAM(ref) FIniData& Data, FName PropertyName, FVector2D NewValue);

	/**
	 * Set global property value as Vector3f type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsVector3f(UPARAM(ref) FIniData& Data, FName PropertyName, FVector3f NewValue);

	/**
	 * Set global property value as IntVector type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsIntVector(UPARAM(ref) FIniData& Data, FName PropertyName, FIntVector NewValue);

	/**
	 * Set global property value as Rotator type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsRotator(UPARAM(ref) FIniData& Data, FName PropertyName, FRotator NewValue);

	/**
	 * Set global property value as Matrix type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsMatrix(UPARAM(ref) FIniData& Data, FName PropertyName, FMatrix NewValue);

	/**
	 * Set global property value as Transform type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsTransform(UPARAM(ref) FIniData& Data, FName PropertyName, FTransform NewValue);

	/**
	 * Set global property value as LinearColor type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsLinearColor(UPARAM(ref) FIniData& Data, FName PropertyName, FLinearColor NewValue);

	/**
	 * Set global property value as InputDeviceId type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsInputDeviceId(UPARAM(ref) FIniData& Data, FName PropertyName, FInputDeviceId NewValue);

	/**
	 * Set global property value as PlatformUserId type
	 *
	 * @param IN Data
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetGlobalPropertyValueAsPlatformUserId(UPARAM(ref) FIniData& Data, FName PropertyName, FPlatformUserId NewValue);

public:
	/**
	 * Get property value as Name type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetPropertyValueAsName(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FName& Value);

	/**
	 * Get property value as Text type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetPropertyValueAsText(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FText& Value);

	/**
	 * Get property value as String type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetPropertyValueAsString(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FString& Value);

	/**
	 * Get property value as int32 type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetPropertyValueAsInt(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, int32& OutValue);

	/**
	 * Get property value as int64 type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetPropertyValueAsInt64(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, int64& OutValue);

	/**
	 * Get property value as bool type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetPropertyValueAsBoolean(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, bool& OutValue);

	/**
	 * Get property value as float type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetPropertyValueAsFloat(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, float& OutValue);

	/**
	 * Get property value as double type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param OUT OutValue
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetPropertyValueAsDouble(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, double& OutValue);

	/**
	 * Get property value as Vector type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN OutConvertedVector
	 * @param OUT OutIsValid
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetPropertyValueAsVector(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FVector& OutConvertedVector, bool& OutIsValid);

	/**
	 * Get property value as Vector3f type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN OutConvertedVector
	 * @param OUT OutIsValid
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetPropertyValueAsVector3f(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FVector3f& OutConvertedVector, bool& OutIsValid);

	/**
	 * Get property value as Vector2D type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN OutConvertedVector2D
	 * @param OUT OutIsValid
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetPropertyValueAsVector2D(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FVector2D& OutConvertedVector2D, bool& OutIsValid);

	/**
	 * Get property value as Rotator type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN OutConvertedRotator
	 * @param OUT OutIsValid
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetPropertyValueAsRotator(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FRotator& OutConvertedRotator, bool& OutIsValid);

	/**
	 * Get property value as LinearColor type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN OutConvertedColor
	 * @param OUT OutIsValid
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "IniParser|IniLibrary"
	)
	static void GetPropertyValueAsLinearColor(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FLinearColor& OutConvertedColor, bool& OutIsValid);

public:
	/**
	 * Set property value as Name type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsName(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FName NewValue);

	/**
	 * Set property value as Text type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsText(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FText NewValue);

	/**
	 * Set property value as String type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsString(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FString NewValue);

	/**
	 * Set property value as Object type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsObject(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, UObject* NewValue);

	/**
	 * Set property value as uint8 type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsByte(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, uint8 NewValue);

	/**
	 * Set property value as int32 type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsInt(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, int32 NewValue);

	/**
	 * Set property value as int64 type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsInt64(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, int64 NewValue);

	/**
	 * Set property value as IntPoint type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsIntPoint(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FIntPoint NewValue);

	/**
	 * Set property value as boolean type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsBool(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, bool bNewValue);

	/**
	 * Set property value as float type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsFloat(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, float NewValue);

	/**
	 * Set property value as double type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsDouble(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, double NewValue);

	/**
	 * Set property value as Vector type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsVector(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FVector NewValue);

	/**
	 * Set property value as Vector2D type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsVector2D(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FVector2D NewValue);

	/**
	 * Set property value as Vector3f type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsVector3f(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FVector3f NewValue);

	/**
	 * Set property value as IntVector type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsIntVector(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FIntVector NewValue);

	/**
	 * Set property value as Rotator type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsRotator(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FRotator NewValue);

	/**
	 * Set property value as Matrix type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsMatrix(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FMatrix NewValue);

	/**
	 * Set property value as Transform type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsTransform(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FTransform NewValue);

	/**
	 * Set property value as LinearColor type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsLinearColor(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FLinearColor NewValue);

	/**
	 * Set property value as InputDeviceId type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsInputDeviceId(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FInputDeviceId NewValue);

	/**
	 * Set property value as PlatformUserId type
	 *
	 * @param IN Data
	 * @param IN SectionName
	 * @param IN PropertyName
	 * @param IN NewValue
	 */
	UFUNCTION(BlueprintCallable, Category = "IniParser|IniLibrary")
	static void SetPropertyValueAsPlatformUserId(UPARAM(ref) FIniData& Data, FName SectionName, FName PropertyName, FPlatformUserId NewValue);

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
