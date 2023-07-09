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
	FORCEINLINE FName GetSectionName() const { return SectionName; }

	FORCEINLINE TArray<FString> GetComments() const { return Comments; }

	FORCEINLINE TMap<FName, FIniProperty> GetProperties() const { return Properties; }

public:
	FIniProperty& AddProperty(const FName& KeyName, const FString& Value);
	bool TryGetProperty(const FName& PropertyName, FIniProperty& OutProperty);

	FIniProperty& GetProperty(const FName& PropertyName);
	bool HasProperty(const FName& PropertyName) const;

	void AddComment(FString Comment);
	void AddUniqueComment(FString Comment);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "IniSection")
	FName SectionName;

	UPROPERTY(BlueprintReadOnly, Category = "IniSection")
	TArray<FString> Comments;

	UPROPERTY(BlueprintReadOnly, Category = "IniSection")
	TMap<FName, FIniProperty> Properties;

public:
	FIniSection()
	{
		SectionName = FName();
		Properties = TMap<FName, FIniProperty>();
		Comments = TArray<FString>();
	}

	FIniSection(FName Name)
	{
		SectionName = Name;
		Properties = TMap<FName, FIniProperty>();
		Comments = TArray<FString>();
	}

	FIniSection(FName Name, TMap<FName, FIniProperty> NewProperties)
	{
		SectionName = Name;
		Properties = NewProperties;
	}

	FIniSection(FName Name, TMap<FName, FIniProperty> NewProperties, TArray<FString> NewComments)
	{
		SectionName = Name;
		Properties = NewProperties;
		Comments = NewComments;
	}

	FIniSection(FName Name, TArray<FString> NewComments)
	{
		SectionName = Name;
		Properties = TMap<FName, FIniProperty>();
		Comments = NewComments;
	}

public:
	FString ToString() const;

public:
	FIniProperty& operator[](const FName& PropertyName);
};