#include "IniData.h"
#include "Kismet/KismetStringLibrary.h"

bool FIniData::HasSection(const FString& SectionName) const
{
	return Sections.Contains(SectionName);
}

FIniSection& FIniData::GetSection(const FString& SectionName)
{
	return Sections[SectionName];
}

bool FIniData::TryGetSection(const FString& SectionName, FIniSection& OutSection)
{
	if (!HasSection(SectionName))
		return false;

	OutSection = GetSection(SectionName);
	return true;
}

FIniSection& FIniData::AddSection(const FString& SectionName)
{
	return Sections.FindOrAdd(SectionName, FIniSection(SectionName));
}

FORCEINLINE FString FIniData::ToString() const
{
	FString StringResult;

	StringResult += TEXT("\n=== .Ini Data ===\n");

	StringResult += TEXT("\n=== Sections ===\n");

	for (auto& Section : Sections)
	{
		StringResult += FString::Printf(TEXT("\n=== %s ===\n"), *Section.Key);

		TArray<FString> Array;

		for (auto& Property : Section.Value.GetProperties())
			Array.Add(Property.Value.ToString());

		StringResult += FString::Printf(TEXT("%s\n"),
			*(UKismetStringLibrary::JoinStringArray(Array, TEXT("\n")))
		);
	}

	return StringResult;
}

FIniSection& FIniData::operator[](const FString& SectionName)
{
	return Sections[SectionName];
}