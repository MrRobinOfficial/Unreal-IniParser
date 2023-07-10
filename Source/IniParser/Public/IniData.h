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
	FORCEINLINE TMap<FName, FIniProperty> GetProperties() const { return Properties; }
	FORCEINLINE bool HasSection(const FName& SectionName) const { return Sections.Contains(SectionName); }
	FORCEINLINE bool HasEmptySections() const { return Sections.IsEmpty(); }
	FORCEINLINE bool HasEmptyProperties() const { return Properties.IsEmpty(); }
	FORCEINLINE bool HasEmptyComments() const { return Comments.IsEmpty(); }

public:
	/**
	 * Find .ini section associated with a specified name.
	 *
	 * @param IN SectionName The name to search for.
	 * @return A pointer to the value associated with the specified name, or nullptr if the name isn't contained in this section.
	 */
	FIniSection* FindSection(const FName& SectionName);

	/**
	 * Add a new .ini section
	 *
	 * @param IN SectionName The key to associate the value with.
	 * @return A reference of .ini section. The reference is only valid until the next change to any key in the map.
	 */
	FIniSection& AddSection(const FName& SectionName);

	/**
	 * Find the value associated with a specified name, or if none exists,
	 * adds a .ini section using the default constructor.
	 *
	 * @param IN SectionName The name to search for.
	 * @return A reference to the value associated with the specified name.
	 */
	FIniSection& FindOrAddSection(const FName& SectionName);

	/**
	 * Tries to get a .ini section based on the name.
	 *
	 * @param IN SectionName The name to search for.
	 * @param OUT OutSection A reference to the .ini section associated with the specified name.
	 * @return A boolean, whether it could find the section.
	 */
	bool TryGetSection(const FName& SectionName, FIniSection& OutSection);

	/**
	 * Get a .ini section based on the name.
	 *
	 * @param IN SectionName The name to search for.
	 * @return A reference to the .ini section associated with the specified name.
	 */
	FIniSection& GetSection(const FName& SectionName);

	/**
	 * Add global comment
	 *
	 * @param IN Comment
	 */
	void AddComment(FString Comment);

	/**
	 * Add unique global comment
	 *
	 * @param IN Comment
	 */
	void AddUniqueComment(FString Comment);

	/**
	 * Find a global property
	 *
	 * @param IN KeyName The name to search for.
	 * @return A pointer to the .ini property associated with the specified name.
	 */
	FIniProperty* FindProperty(const FName& KeyName);

	/**
	 * Find or add a global property
	 *
	 * @param IN KeyName The name to search for.
	 * @param IN Value The value to add to .ini property
	 * @return A reference to the .ini property associated with the specified name.
	 */
	FIniProperty& FindOrAddProperty(const FName& KeyName, const FString& Value);

	/**
	 * Add a global property
	 *
	 * @param IN KeyName The name to search for.
	 * @param IN Value The value to add to .ini property
	 * @return A reference to the newly created .ini property
	 */
	FIniProperty& AddProperty(const FName& KeyName, const FString& Value);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "IniData")
	TMap<FName, FIniSection> Sections;

	/// @brief Global comments
	UPROPERTY(BlueprintReadOnly, Category = "IniData")
	TArray<FString> Comments;

	/// @brief Global properties
	UPROPERTY(BlueprintReadOnly, Category = "IniSection")
	TMap<FName, FIniProperty> Properties;

public:
	/**
	 * Convert .ini data to a stringable format
	 *
	 * @return A string format of .ini data struct
	 */
	FString ToString() const;

public:
	FIniSection& operator[](const FName& SectionName);
};