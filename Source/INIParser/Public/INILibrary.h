// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "INILibrary.generated.h"

typedef TMap<FString, struct FIniProperty> PropertyCollection;
typedef TMap<FString, struct FIniSection> SectionCollection;

USTRUCT(BlueprintType)
struct FIniProperty
{
	GENERATED_BODY()

public:
	FString GetKeyName() const { return KeyName; }

	FString GetValue() const { return Value; }
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString KeyName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Value;

public:
	FIniProperty()
	{
		KeyName = FString();
		Value = FString();
	}

	FIniProperty(FString NewKeyName)
	{
		KeyName = NewKeyName;
		Value = FString();
	}

	FIniProperty(FString NewKeyName, FString NewValue)
	{
		KeyName = NewKeyName;
		Value = NewValue;
	}

	FString ToString() const;

	void operator=(const uint8_t& NewValue);
	void operator=(const int& NewValue);
	void operator=(const int64& NewValue);
	void operator=(const FIntPoint& NewValue);
	void operator=(const bool& NewValue);
	void operator=(const double& NewValue);
	void operator=(const float& NewValue);
	void operator=(const FVector& NewValue);
	void operator=(const FVector3f& NewValue);
	void operator=(const FVector2D& NewValue);
	void operator=(const FIntVector& NewValue);
	void operator=(const FRotator& NewValue);
	void operator=(const FMatrix& NewValue);
	void operator=(const FName& NewValue);
	void operator=(const FString& NewValue);
	void operator=(const FText& NewValue);
	void operator=(UObject* NewValue);
	void operator=(const FTransform& NewValue);
	void operator=(const FLinearColor& NewValue);
	void operator=(const FInputDeviceId& NewValue);
	void operator=(const FPlatformUserId& NewValue);

	operator FString() const;
};

USTRUCT(BlueprintType)
struct FIniSection
{
	GENERATED_BODY()

public:
	FString GetSectionName() const { return SectionName; }

	TArray<FString> GetComments() const { return Comments; }

	TMap<FString, FIniProperty> GetProperties() const { return Properties; }

public:
	void AddProperty(FIniProperty Property, bool bOverwriteValueIfExist = false);

	bool DoesPropertyExist(const FString& Name) const;

	bool TryFindPropertyByName(FString Name, FIniProperty*& OutProperty);
	bool TryFindOrAddPropertyByName(FString Name, FIniProperty& OutProperty);

	FIniProperty& FindOrAddPropertyByName(FString Name);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString SectionName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FString> Comments;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FString, FIniProperty> Properties;

public:
	FIniSection()
	{
		SectionName = FString();
		Properties = TMap<FString, FIniProperty>();
		Comments = TArray<FString>();
	}

	FIniSection(FString Name)
	{
		SectionName = Name;
		Properties = TMap<FString, FIniProperty>();
		Comments = TArray<FString>();
	}

	FIniSection(FString Name, PropertyCollection NewProperties)
	{
		SectionName = Name;
		Properties = NewProperties;
	}

	FIniSection(FString Name, PropertyCollection NewProperties, TArray<FString> NewComments)
	{
		SectionName = Name;
		Properties = NewProperties;
		Comments = NewComments;
	}

	FIniSection(FString Name, TArray<FString> NewComments)
	{
		SectionName = Name;
		Properties = TMap<FString, FIniProperty>();
		Comments = NewComments;
	}

	FIniProperty& operator[](const FString& PropertyName);

	FString ToString() const;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "INIParser.INILibrary.MakeIniDataStruct"))
struct FIniData
{
	GENERATED_BODY()

public:
	const SectionCollection& GetSections() const { return Sections; }

public:
	void AddSection(FIniSection Section, bool bOverwriteValueIfExist = false);

	bool DoesSectionExist(const FString& Name) const;

	FIniSection& FindOrAddSectionByName(FString Name);

	bool TryFindSectionByName(FString Name, FIniSection*& OutSection);
	bool TryFindOrAddSectionByName(FString Name, FIniSection& OutSection);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FString, FIniSection> Sections;

public:	
	FString ToString() const;

	FIniSection& operator[](const FString& SectionName);
};

UCLASS()
class INIPARSER_API UINILibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(
		BlueprintCallable,
		Category = "INIParser|INILibrary",
		meta = (DisplayName = "Parse .Ini File")
	)
	static FIniData ParseIniFile(FString Data);

	UFUNCTION(
		BlueprintPure,
		Category = "INIParser|INILibrary",
		meta = (BlueprintThreadSafe)
	)
	static FIniData MakeIniDataStruct(TMap<FString, FIniSection> Sections, TMap<FString, FIniProperty> Properties);

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "INIParser|INILibrary"
	)
	static FString Conv_IniDataToString(const FIniData& Data);

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "INIParser|INILibrary"
	)
	static const FString ReadValueAsStringFromIniData(
		UPARAM(ref) FIniData& Data,
		FString SectionName,
		FString PropertyName
	);

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "INIParser|INILibrary"
	)
	static void WriteValueAsStringFromIniData(
		UPARAM(ref) FIniData& Data,
		FString SectionName,
		FString PropertyName,
		FString NewValue
	);

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "INIParser|INILibrary"
	)
	static bool TryGetSectionFromIniData(
		UPARAM(ref) FIniData& Data,
		FString SectionName,
		FIniSection& OutSection
	);

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "INIParser|INILibrary"
	)
	static bool TryGetPropertyFromIniSection(
		UPARAM(ref) FIniSection& Section,
		FString PropertyName,
		FIniProperty& OutProperty
	);

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "INIParser|INILibrary"
	)
	static TArray<FIniProperty> GetAllPropertiesFromIniData(
		UPARAM(ref) FIniData& Data,
		FString PropertyName
	);

protected:
	static void AppendBuffer(char* Buffer, char Char);
	static void TrimBuffer(char* Buffer);
};
