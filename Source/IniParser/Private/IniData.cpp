// Copyright 2023 MrRobin. All Rights Reserved.

#include "IniData.h"
#include "Kismet/KismetStringLibrary.h"

FIniSection* FIniData::FindSection(const FName& Key)
{
	return Sections.Find(Key);
}

FIniSection FIniData::FindRefSection(const FName& Key)
{
	return Sections.FindRef(Key);
}

FIniSection& FIniData::FindOrAddSection(const FName& Key)
{
	return Sections.FindOrAdd(Key, FIniSection());
}

FIniSection& FIniData::AddSection(const FName& Key)
{
	return Sections.Add(Key, FIniSection());
}

FIniSection& FIniData::GetSection(const FName& SectionName)
{
	return Sections[SectionName];
}

void FIniData::AddComment(FString Comment)
{
	Comments.Add(Comment);
}

void FIniData::AddUniqueComment(FString Comment)
{
	Comments.AddUnique(Comment);
}

FIniProperty* FIniData::FindProperty(const FName& Key)
{
	return Properties.Find(Key);
}

FIniProperty FIniData::FindRefProperty(const FName& Key)
{
	return Properties.FindRef(Key);
}

FIniProperty& FIniData::FindOrAddProperty(const FName& Key, const FString& Value)
{
	return Properties.FindOrAdd(Key, FIniProperty(Value));
}

FIniProperty& FIniData::AddProperty(const FName& Key, const FString& Value)
{
	return Properties.Add(Key, FIniProperty(Value));
}

FIniProperty& FIniData::GetProperty(const FName& PropertyName)
{
	return Properties[PropertyName];
}

FIniSection& FIniData::operator[](const FName& SectionName)
{
	return Sections[SectionName];
}