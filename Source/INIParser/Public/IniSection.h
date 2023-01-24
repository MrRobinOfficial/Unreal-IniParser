// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IniProperty.h"
#include "IniSection.generated.h"

USTRUCT(BlueprintType)
struct FIniSection
{
	GENERATED_BODY()

public:
	FString GetSectionName() const { return SectionName; }

	TArray<FString> GetComments() const { return Comments; }

	TMap<FString, FIniProperty> GetProperties() const { return Properties; }

public:
	FIniProperty& AddProperty(const FString& KeyName, const FString& Value);
	bool TryGetProperty(const FString& PropertyName, FIniProperty& OutProperty);
	FIniProperty& GetProperty(const FString& PropertyName);
	bool HasProperty(const FString& PropertyName) const;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IniSection")
	FString SectionName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IniSection")
	TArray<FString> Comments;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IniSection")
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

	FIniSection(FString Name, TMap<FString, FIniProperty> NewProperties)
	{
		SectionName = Name;
		Properties = NewProperties;
	}

	FIniSection(FString Name, TMap<FString, FIniProperty> NewProperties, TArray<FString> NewComments)
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

public:
	FString ToString() const;

public:
	FIniProperty& operator[](const FString& PropertyName);
};