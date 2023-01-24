// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IniSection.h"
#include "IniData.generated.h"

USTRUCT(BlueprintType, meta = (HasNativeMake = "IniParser.IniLibrary.MakeIniDataStruct"))
struct FIniData
{
	GENERATED_BODY()

public:
	FIniData() {}

	FIniData(
		TMap<FString, FIniSection> NewSections)
	{
		Sections = NewSections;
	}

public:
	const TMap<FString, FIniSection>& GetSections() const { return Sections; }

public:
	FIniSection& AddSection(const FString& SectionName);
	bool TryGetSection(const FString& SectionName, FIniSection& OutSection);
	FIniSection& GetSection(const FString& SectionName);
	bool HasSection(const FString& SectionName) const;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="IniData")
	TMap<FString, FIniSection> Sections;

public:	
	FString ToString() const;

public:
	FIniSection& operator[](const FString& SectionName);
};