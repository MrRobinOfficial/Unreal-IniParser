// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IniSection.h"
#include "IniData.generated.h"

USTRUCT(BlueprintType, meta = (HasNativeMake = "IniParser.IniLibrary.MakeIniData"))
struct FIniData
{
	GENERATED_BODY()

private:
	/// @brief Global comments
	UPROPERTY(EditAnywhere, Category = "Details", meta = (AllowPrivateAccess = true))
	TArray<FString> Comments;

	/// @brief Global properties
	UPROPERTY(EditAnywhere, Category = "Details", meta = (AllowPrivateAccess = true))
	TMap<FName, FIniProperty> Properties;

	UPROPERTY(EditAnywhere, Category = "Details", meta = (AllowPrivateAccess = true))
	TMap<FName, FIniSection> Sections;

public:
	FIniData()
	{ }

	FIniData(TMap<FName, FIniSection> NewSections)
		: Sections(NewSections)
	{ }

public:
	FORCEINLINE int32 GetNumOfSections() const { return Sections.Num(); }
	FORCEINLINE int32 GetNumOfComments() const { return Comments.Num(); }
	FORCEINLINE int32 GetNumOfProperties() const { return Properties.Num(); }
	FORCEINLINE TArray<FString> GetComments() const { return Comments; }
	FORCEINLINE TMap<FName, FIniProperty> GetProperties() const { return Properties; }
	FORCEINLINE TMap<FName, FIniSection> GetSections() const { return Sections; }
	FORCEINLINE bool HasComment(const FString& Comment) const { return Comments.Contains(Comment); }
	FORCEINLINE bool HasSection(const FName& SectionName) const { return Sections.Contains(SectionName); }
	FORCEINLINE bool HasEmptyComments() const { return Comments.IsEmpty(); }
	FORCEINLINE bool HasEmptySections() const { return Sections.IsEmpty(); }
	FORCEINLINE bool HasEmptyProperties() const { return Properties.IsEmpty(); }

public:
	/**
	 * Find .ini section associated with a specified name.
	 *
	 * @param IN Key The name to search for.
	 * @return A pointer to the value associated with the specified name, or nullptr if the name isn't contained in this section.
	 */
	FIniSection* FindSection(const FName& Key);

	/**
	 * Find .ini section associated with a specified name.
	 *
	 * @param IN Key The name to search for.
	 * @return A section to the value associated with the specified name, or empty if the name isn't contained in this section.
	 */
	FIniSection FindRefSection(const FName& Key);

	/**
	 * Find the value associated with a specified name, or if none exists,
	 * adds a .ini section using the default constructor.
	 *
	 * @param IN Key The name to search for.
	 * @return A reference to the value associated with the specified name.
	 */
	FIniSection& FindOrAddSection(const FName& Key);

	/**
	 * Add a new .ini section
	 *
	 * @param IN SectionName The key to associate the value with.
	 * @return A reference of .ini section. The reference is only valid until the next change to any key in the map.
	 */
	FIniSection& AddSection(const FName& Key);

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
	FIniProperty* FindProperty(const FName& Key);

	/**
	 * Find .ini property associated with a specified name.
	 *
	 * @param IN Key The name to search for.
	 * @return A property to the value associated with the specified name, or empty if the name isn't contained in this property.
	 */
	FIniProperty FindRefProperty(const FName& Key);

	/**
	 * Find or add a global property
	 *
	 * @param IN Key The name to search for.
	 * @param IN Value The value to add to .ini property
	 * @return A reference to the .ini property associated with the specified name.
	 */
	FIniProperty& FindOrAddProperty(const FName& Key, const FString& Value);

	/**
	 * Add a global property
	 *
	 * @param IN Key The name to search for.
	 * @param IN Value The value to add to .ini property
	 * @return A reference to the newly created .ini property
	 */
	FIniProperty& AddProperty(const FName& Key, const FString& Value);

public:
	FIniSection& operator[](const FName& SectionName);
};