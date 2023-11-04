// Copyright 2023 MrRobin. All Rights Reserved.

#include "IniSection.h"

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

FIniProperty* FIniSection::FindProperty(const FName& Key)
{
	return Properties.Find(Key);
}

FIniProperty FIniSection::FindRefProperty(const FName& Key)
{
	return Properties.FindRef(Key);
}

FIniProperty& FIniSection::FindOrAddProperty(const FName& Key, const FString& Value)
{
	return Properties.FindOrAdd(Key, FIniProperty(Value));
}

FIniProperty& FIniSection::AddProperty(const FName& Key, const FString& Value)
{
	return Properties.Add(Key, FIniProperty(Value));
}

FIniProperty& FIniSection::operator[](const FName& PropertyName)
{
	return Properties[PropertyName];
}