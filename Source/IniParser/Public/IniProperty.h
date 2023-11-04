// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetStringLibrary.h"
#include "IniProperty.generated.h"

/* .ini property - Every property has a name and a value, delimited by an equals sign (=). The name appears to the left of the equals sign. In the Windows implementation the equal sign and the semicolon are reserved characters and cannot appear in the key. The value can contain any character. */
USTRUCT(BlueprintType)
struct FIniProperty
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Details", meta = (AllowPrivateAccess = true))
	FString Value;

public:
	FIniProperty()
		: Value()
	{ }

	FIniProperty(FString NewValue)
		: Value(NewValue)
	{ }

public:
	/**
	 * Get value as a raw String (without double quotes)
	 *
	 * @return A string
	 */
	FORCEINLINE FString GetValueAsRawString() const { return Value.TrimStartAndEnd(); }


	/**
	 * Get value as a String with double quotes
	 *
	 * @return A string
	 */
	FORCEINLINE FString GetValueAsString() const { return Stringfy(Value); }

	/**
	 * Get value as a String with double quotes (if whitespace detected)
	 *
	 * @return A string
	 */
	FORCEINLINE FString GetValueReadableString() const
	{
		return Value.MatchesWildcard(TEXT("* *")) ? Stringfy(Value) : Value;
	}

	/**
	 * Get value as a Text
	 *
	 * @return A text
	 */
	FORCEINLINE FText GetValueAsText() const { return FText::FromString(Value); }

	/**
	 * Get value as a Name
	 *
	 * @return A name
	 */
	FORCEINLINE FName GetValueAsName() const { return UKismetStringLibrary::Conv_StringToName(Value); }

	/**
	 * Get value as a uint8
	 *
	 * @param OUT OutValue
	 */
	FORCEINLINE void GetValueAsByte(uint8& OutValue) const { return LexFromString(OutValue, *Value); }

	/**
	 * Get value as a int32
	 *
	 * @param OUT OutValue
	 */
	FORCEINLINE void GetValueAsInt(int32& OutValue) const { return LexFromString(OutValue, *Value); }

	/**
	 * Get value as a int64
	 *
	 * @param OUT OutValue
	 */
	FORCEINLINE void GetValueAsInt64(int64& OutValue) const { return LexFromString(OutValue, *Value); }

	/**
	 * Get value as a boolean
	 *
	 * @param OUT OutValue
	 */
	FORCEINLINE void GetValueAsBoolean(bool& OutValue) const { return LexFromString(OutValue, *Value); }

	/**
	 * Get value as a float
	 *
	 * @param OUT OutValue
	 */
	FORCEINLINE void GetValueAsFloat(float& OutValue) const { return LexFromString(OutValue, *Value); }

	/**
	 * Get value as a double
	 *
	 * @param OUT OutValue
	 */
	FORCEINLINE void GetValueAsDouble(double& OutValue) const { return LexFromString(OutValue, *Value); }

	/**
	 * Get value as a LinearColor
	 *
	 * @param OUT OutConvertedColor
	 * @param OUT OutIsValid
	 */
	FORCEINLINE void GetValueAsColor(FLinearColor& OutConvertedColor, bool& OutIsValid) const
	{
		UKismetStringLibrary::Conv_StringToColor(Value, OutConvertedColor, OutIsValid);
	}

	/**
	 * Get value as a Rotator
	 *
	 * @param OUT OutConvertedRotator
	 * @param OUT OutIsValid
	 */
	FORCEINLINE void GetValueAsRotator(FRotator& OutConvertedRotator, bool& OutIsValid) const
	{
		UKismetStringLibrary::Conv_StringToRotator(Value, OutConvertedRotator, OutIsValid);
	}

	/**
	 * Get value as a Vector
	 *
	 * @param OUT OutConvertedVector
	 * @param OUT OutIsValid
	 */
	FORCEINLINE void GetValueAsVector(FVector& OutConvertedVector, bool& OutIsValid) const
	{
		UKismetStringLibrary::Conv_StringToVector(Value, OutConvertedVector, OutIsValid);
	}

	/**
	 * Get value as a Vector2D
	 *
	 * @param OUT OutConvertedVector2D
	 * @param OUT OutIsValid
	 */
	FORCEINLINE void GetValueAsVector2D(FVector2D& OutConvertedVector2D, bool& OutIsValid) const
	{
		UKismetStringLibrary::Conv_StringToVector2D(Value, OutConvertedVector2D, OutIsValid);
	}

	/**
	 * Get value as a Vector3f
	 *
	 * @param OUT OutConvertedVector
	 * @param OUT OutIsValid
	 */
	FORCEINLINE void GetValueAsVector3f(FVector3f& OutConvertedVector, bool& OutIsValid) const
	{
		UKismetStringLibrary::Conv_StringToVector3f(Value, OutConvertedVector, OutIsValid);
	}

public:
	/**
	 * Set value as a String type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsString(FString NewValue);

	/**
	 * Set value as a Text type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsText(FText NewValue);

	/**
	 * Set value as a Name type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsName(FName NewValue);

	/**
	 * Set value as a Object type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsObject(UObject* NewValue);

	/**
	 * Set value as a uint8 type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsByte(uint8 NewValue);

	/**
	 * Set value as a int32 type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsInt(int32 NewValue);

	/**
	 * Set value as a int64 type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsInt64(int64 NewValue);

	/**
	 * Set value as a IntPoint type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsIntPoint(FIntPoint NewValue);

	/**
	 * Set value as a boolean type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsBoolean(bool bNewValue);

	/**
	 * Set value as a float type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsFloat(float NewValue);

	/**
	 * Set value as a double type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsDouble(double NewValue);

	/**
	 * Set value as a Vector type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsVector(FVector NewValue);

	/**
	 * Set value as a Vector2D type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsVector2D(FVector2D NewValue);

	/**
	 * Set value as a Vector3f type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsVector3f(FVector3f NewValue);

	/**
	 * Set value as a IntVector type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsIntVector(FIntVector NewValue);

	/**
	 * Set value as a Rotator type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsRotator(FRotator NewValue);

	/**
	 * Set value as a Matrix type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsMatrix(FMatrix NewValue);

	/**
	 * Set value as a Transform type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsTransform(FTransform NewValue);

	/**
	 * Set value as a LinearColor type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsColor(FLinearColor NewValue);

	/**
	 * Set value as a InputDeviceId type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsInputDeviceId(FInputDeviceId NewValue);

	/**
	 * Set value as a PlatformUserId type
	 *
	 * @param IN NewValue
	 */
	void SetValueAsPlatformUserId(FPlatformUserId NewValue);

private:
	// Create a new string, surrounded by double quotes.
	FORCEINLINE FString Stringfy(const FString& NewValue) const { return TEXT("\"") + Value + TEXT("\""); }
};