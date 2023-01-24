#include "IniSection.h"

FORCEINLINE FString FIniSection::ToString() const { return SectionName; }

FIniProperty& FIniSection::operator[](const FString& PropertyName)
{
	return Properties[PropertyName];
}

bool FIniSection::HasProperty(const FString& PropertyName) const
{
	return Properties.Contains(PropertyName);
}

FIniProperty& FIniSection::GetProperty(const FString& PropertyName)
{
	return Properties[PropertyName];
}

bool FIniSection::TryGetProperty(const FString& PropertyName, FIniProperty& OutProperty)
{
	if (!HasProperty(PropertyName))
		return false;

	OutProperty = GetProperty(PropertyName);
	return true;
}

FIniProperty& FIniSection::AddProperty(const FString& KeyName, const FString& Value)
{
	return Properties.FindOrAdd(KeyName, FIniProperty(KeyName, Value));
}