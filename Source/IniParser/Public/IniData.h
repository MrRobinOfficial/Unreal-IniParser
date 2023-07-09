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

	FIniData(TMap<FName, FIniSection> NewSections)
		: Sections(NewSections)
	{ }

public:
	FORCEINLINE TMap<FName, FIniSection> GetSections() const { return Sections; }

	FORCEINLINE TArray<FString> GetComments() const { return Comments; }

	FORCEINLINE bool HasSection(const FName& SectionName) const
	{
		return Sections.Contains(SectionName);
	}

public:
	/**
	 * Find .ini section associated with a specified name.
	 *
	 * @param SectionName The name to search for.
	 * @return A pointer to the value associated with the specified name, or nullptr if the name isn't contained in this section.
	 */
	FIniSection* FindSection(const FName& SectionName);

	/**
	 * Add a new .ini section
	 *
	 * @param SectionName The key to associate the value with.
	 * @return A reference of .ini section. The reference is only valid until the next change to any key in the map.
	 */
	FIniSection& AddSection(const FName& SectionName);

	/**
	 * Find the value associated with a specified name, or if none exists,
	 * adds a .ini section using the default constructor.
	 *
	 * @param SectionName The name to search for.
	 * @return A reference to the value associated with the specified name.
	 */
	FIniSection& FindOrAddSection(const FName& SectionName);

	/* Lorem Ipsum */
	bool TryGetSection(const FName& SectionName, FIniSection& OutSection);

	/* Lorem Ipsum */
	FIniSection& GetSection(const FName& SectionName);

	/* Add comment to global comments */
	void AddComment(FString Comment);

	/* Add comment to global comments */
	void AddUniqueComment(FString Comment);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "IniData")
	TMap<FName, FIniSection> Sections;

	UPROPERTY(BlueprintReadOnly, Category = "IniData")
	TArray<FString> Comments;

public:
	/* Convert .ini data to a stringable format */
	FString ToString() const;

public:
	FIniSection& operator[](const FName& SectionName);
};