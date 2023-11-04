// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IniProperty.h"
#include "IniSection.generated.h"

/* .ini section - The section name appears on a line by itself, in square brackets ([ and ]). All keys after the section declaration are associated with that section. There is no explicit "end of section" delimiter; sections end at the next section declaration, or at the end of the file. Sections cannot be nested. */
USTRUCT(BlueprintType, meta = (HasNativeMake = "IniParser.IniLibrary.MakeIniSection"))
struct FIniSection
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Details", meta = (AllowPrivateAccess = true))
	TArray<FString> Comments;

	UPROPERTY(EditAnywhere, Category = "Details", meta = (AllowPrivateAccess = true))
	TMap<FName, FIniProperty> Properties;

public:
	FORCEINLINE int32 GetNumOfComments() const { return Comments.Num(); }
	FORCEINLINE int32 GetNumOfProperties() const { return Properties.Num(); }
	FORCEINLINE TArray<FString> GetComments() const { return Comments; }
	FORCEINLINE TMap<FName, FIniProperty> GetProperties() const { return Properties; }
	FORCEINLINE bool HasComment(const FString& Comment) const { return Comments.Contains(Comment); }
	FORCEINLINE bool HasProperty(const FName& PropertyName) const { return Properties.Contains(PropertyName); }
	FORCEINLINE bool HasEmptyComments() const { return Comments.IsEmpty(); }
	FORCEINLINE bool HasEmptyProperties() const { return Properties.IsEmpty(); }

public:
	/**
	 * Find .ini property associated with a specified name.
	 *
	 * @param IN KeyName The name to search for.
	 * @return A pointer to the value associated with the specified name, or nullptr if the name isn't contained in this property.
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
	 * Find the value associated with a specified name, or if none exists,
	 * adds a .ini property using the default constructor.
	 *
	 * @param IN Key The name to search for.
	 * @param IN Value The value to associate the property with.
	 * @return A reference to the value associated with the specified name.
	 */
	FIniProperty& FindOrAddProperty(const FName& Key, const FString& Value);

	/**
	 * Add a new .ini property
	 *
	 * @param IN Key The key to associate the property with.
	 * @param IN Value The value to associate the property with.
	 * @return A property of .ini property. The reference is only valid until the next change to any key in the map.
	 */
	FIniProperty& AddProperty(const FName& Key, const FString& Value);

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

public:
	FIniSection()
		: Comments()
		, Properties()
	{ }

	FIniSection(TMap<FName, FIniProperty> NewProperties)
		: Comments()
		, Properties(NewProperties)
	{ }

	FIniSection(TMap<FName, FIniProperty> NewProperties, TArray<FString> NewComments)
		: Comments(NewComments)
		, Properties(NewProperties)
	{ }

	FIniSection(TArray<FString> NewComments)
		: Comments(NewComments)
		, Properties()
	{ }

public:
	FIniProperty& operator[](const FName& PropertyName);
};