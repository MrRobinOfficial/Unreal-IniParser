// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IniProperty.h"
#include "IniSection.generated.h"

/* .ini section - The section name appears on a line by itself, in square brackets ([ and ]). All keys after the section declaration are associated with that section. There is no explicit "end of section" delimiter; sections end at the next section declaration, or at the end of the file. Sections cannot be nested. */
USTRUCT(BlueprintType)
struct FIniSection
{
	GENERATED_BODY()

public:
	FORCEINLINE FName GetSectionName() const { return SectionName; }
	FORCEINLINE TArray<FString> GetComments() const { return Comments; }
	FORCEINLINE TMap<FName, FIniProperty> GetProperties() const { return Properties; }
	FORCEINLINE bool HasProperty(const FName& PropertyName) const { return Properties.Contains(PropertyName); }
	FORCEINLINE bool HasEmptyProperties() const { return Properties.IsEmpty(); }
	FORCEINLINE bool HasEmptyComments() const { return Comments.IsEmpty(); }

public:
	/**
	 * Find .ini property associated with a specified name.
	 *
	 * @param IN KeyName The name to search for.
	 * @return A pointer to the value associated with the specified name, or nullptr if the name isn't contained in this property.
	 */
	FIniProperty* FindProperty(const FName& KeyName);

	/**
	 * Find the value associated with a specified name, or if none exists,
	 * adds a .ini property using the default constructor.
	 *
	 * @param IN KeyName The name to search for.
	 * @param IN Value The value to associate the property with.
	 * @return A reference to the value associated with the specified name.
	 */
	FIniProperty& FindOrAddProperty(const FName& KeyName, const FString& Value);

	/**
	 * Add a new .ini property
	 *
	 * @param IN KeyName The key to associate the property with.
	 * @param IN Value The value to associate the property with.
	 * @return A reference of .ini property. The reference is only valid until the next change to any key in the map.
	 */
	FIniProperty& AddProperty(const FName& KeyName, const FString& Value);

	/**
	 * Tries to get a .ini property based on the name.
	 *
	 * @param IN PropertyName The name to search for.
	 * @param OUT OutProperty A reference to the .ini property associated with the specified name.
	 * @return A boolean, whether it could find the property.
	 */
	bool TryGetProperty(const FName& PropertyName, FIniProperty& OutProperty);

	/**
	 * Get a .ini property based on the name.
	 *
	 * @param IN PropertyName The name to search for.
	 * @return A reference to the .ini property associated with the specified name.
	 */
	FIniProperty& GetProperty(const FName& PropertyName);

	/**
	 * Add comment
	 *
	 * @param IN Comment
	 */
	void AddComment(FString Comment);

	/**
	 * Add unique comment
	 *
	 * @param IN Comment
	 */
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
		: SectionName(NAME_None)
		, Comments()
		, Properties()
	{ }

	FIniSection(FName NewName)
		: SectionName(NewName)
		, Comments()
		, Properties()
	{ }

	FIniSection(FName NewName, TMap<FName, FIniProperty> NewProperties)
		: SectionName(NewName)
		, Comments()
		, Properties(NewProperties)
	{ }

	FIniSection(FName NewName, TMap<FName, FIniProperty> NewProperties, TArray<FString> NewComments)
		: SectionName(NewName)
		, Comments(NewComments)
		, Properties(NewProperties)
	{ }

	FIniSection(FName NewName, TArray<FString> NewComments)
		: SectionName(NewName)
		, Comments(NewComments)
		, Properties()
	{ }

public:
	/**
	 * Get a string based on .ini section's name
	 *
	 * @return A string based on it's section name
	 */
	FString ToString() const;

public:
	FIniProperty& operator[](const FName& PropertyName);
};