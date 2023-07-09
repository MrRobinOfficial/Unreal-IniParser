#include "IniData.h"
#include "Kismet/KismetStringLibrary.h"

FIniSection& FIniData::GetSection(const FName& SectionName)
{
	return Sections[SectionName];
}

bool FIniData::TryGetSection(const FName& SectionName, FIniSection& OutSection)
{
	if (!HasSection(SectionName))
		return false;

	OutSection = GetSection(SectionName);
	return true;
}

FIniSection* FIniData::FindSection(const FName& SectionName)
{
	return Sections.Find(SectionName);
}

FIniSection& FIniData::AddSection(const FName& SectionName)
{
	return Sections.Add(SectionName, FIniSection(SectionName));
}

FIniSection& FIniData::FindOrAddSection(const FName& SectionName)
{
	return Sections.FindOrAdd(SectionName, FIniSection(SectionName));
}

void FIniData::AddComment(FString Comment)
{
	Comments.Add(Comment);
}

void FIniData::AddUniqueComment(FString Comment)
{
	Comments.AddUnique(Comment);
}

FString FIniData::ToString() const
{
	TStringBuilder<256> SB;

	SB.Append(TEXT("\r\n=== .Ini Data ===\r\n"));
	SB.Append(TEXT("\r\n=== Sections ===\r\n"));

	for (auto& Section : Sections)
	{
		SB.Append(FString::Printf(TEXT("\r\n=== %s ===\r\n"), *Section.Key.ToString()));

		TArray<FString> Array;

		for (auto& Property : Section.Value.GetProperties())
			Array.Add(Property.Value.ToString());

		SB.Append(FString::Printf(TEXT("%s\r\n"),
			*(UKismetStringLibrary::JoinStringArray(Array, TEXT("\n")))
		));
	}

	return SB.ToString();
}

FIniSection& FIniData::operator[](const FName& SectionName)
{
	return Sections[SectionName];
}