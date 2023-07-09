#include "IniSection.h"

FString FIniSection::ToString() const { return SectionName.ToString(); }

FIniProperty& FIniSection::operator[](const FName& PropertyName)
{
	return Properties[PropertyName];
}

bool FIniSection::HasProperty(const FName& PropertyName) const
{
	return Properties.Contains(PropertyName);
}

void FIniSection::AddComment(FString Comment)
{
	Comments.Add(Comment);
}

void FIniSection::AddUniqueComment(FString Comment)
{
	Comments.AddUnique(Comment);
}

FIniProperty& FIniSection::GetProperty(const FName& PropertyName)
{
	return Properties[PropertyName];
}

bool FIniSection::TryGetProperty(const FName& PropertyName, FIniProperty& OutProperty)
{
	if (!HasProperty(PropertyName))
		return false;

	OutProperty = GetProperty(PropertyName);
	return true;
}

FIniProperty& FIniSection::AddProperty(const FName& KeyName, const FString& Value)
{
	return Properties.FindOrAdd(KeyName, FIniProperty(KeyName, Value));
}