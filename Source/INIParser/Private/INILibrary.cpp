// Copyright 2023 MrRobin. All Rights Reserved.

#include "INILibrary.h"

TArray<FString> UINILibrary::LoadINIFile(FString FilePath)
{
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
		return TArray<FString>();

	TArray<FString> Result = TArray<FString>();
	FFileHelper::LoadFileToStringArray(Result, *FilePath);
	return Result;
}

bool UINILibrary::TryLoadINIFile(FString FilePath, TArray<FString>& OutContents)
{
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
		return false;

	return FFileHelper::LoadFileToStringArray(OutContents, *FilePath);
}

void UINILibrary::WriteINIFile(FString FilePath, TArray<FString> Contents)
{
	IPlatformFile& File = FPlatformFileManager::Get().GetPlatformFile();

	FFileHelper::SaveStringArrayToFile(Contents, *FilePath);
}

bool UINILibrary::TryWriteINIFile(FString FilePath, TArray<FString> Contents)
{
	return FFileHelper::SaveStringArrayToFile(Contents, *FilePath);
}

TArray<FString> UINILibrary::ParseINIFile(FString Data)
{
	char Buffer[256];
	*Buffer = '\0';

	char CurrentSection[256];
	*CurrentSection = '\0';

	char CurrentKey[256];
	char CurrentValue[256];

	/*
	* 0 - Ready for .Ini data
	* 1 - Comment started
	* 2 - Section name started
	* 3 - Key started
	* 4 - Key finished
	* 5 - Ready for value
	* 6 - Value started
	* 7 - Invalid key format
	*/
	int32_t State = 0;

	for (auto It = Data.CreateConstIterator(); It; ++It)
	{
		char Char = Data[It.GetIndex()];

		if (State == 0) // Waiting for .ini data
		{
			if (Char == ';')
				State = 1; // Start comment
			else if (Char == '[')
				State = 2; // Start section name
			else if (Char != ' ' && Char != '\n' && Char != '\t')
			{
				AppendBuffer(Buffer, Char);
				State = 3; // Start key
			}
		}
		else if (State == 1) // Reading comment
		{
			if (Char == '\n')
				State = 0; // End comment
		}
		else if (State == 2) // Section name started
		{
			if (Char == ']') // End section name
			{
				memcpy(CurrentSection, Buffer, 256 * sizeof(char));
				*Buffer = '\0';
				State = 0;
			}
			else if (Char == '\n') // Invalid section name (discard)
			{
				*Buffer = '\0';
				State = 0;
			}
			else
				AppendBuffer(Buffer, Char);
		}
		else if (State == 3) // Key started
		{
			if (Char == ' ' || Char == '\t')
			{
				memcpy(CurrentKey, Buffer, 256 * sizeof(char));
				*Buffer = '\0';
				State = 4; // End key
			}
			else if (Char == '\n') // Invalid key (discard)
				State = 0;
			else
				AppendBuffer(Buffer, Char);
		}
		else if (State == 4) // End of key
		{
			if (Char == '=')
				State = 5; // Ready for value
			else if (Char == '\n')
				State = 0; // Invalid key value
			else if (Char != ' ' && Char != '\t')
				State = 7; // Invalid key format
		}
		else if (State == 5) // Ready for value
		{
			if (Char == '\n')
				State = 0; // Invalid key value
			else if (Char != ' ' && Char != '\t')
			{
				AppendBuffer(Buffer, Char);
				State = 6; // Begin value
			}
		}
		else if (State == 6) // Start of value
		{
			if (Char == '\n')
			{
				TrimBuffer(Buffer);
				memcpy(CurrentValue, Buffer, 256 * sizeof(char));
				*Buffer = '\0';
				State = 0;
			}
			else
				AppendBuffer(Buffer, Char);
		}
		else if (State == 7) // Invalid key format
		{
			if (Char == '\n')
				State = 0;
		}
	}

	return TArray<FString>();
}

bool UINILibrary::TryParseINIFile(FString Data, TArray<FString>& OutContents)
{
	return false;
}

void UINILibrary::AppendBuffer(char* Buffer, const char Char)
{
	char* CharPtr;

	for (CharPtr = Buffer; *CharPtr; CharPtr++);

	CharPtr[0] = Char;
	CharPtr[1] = '\0';
}

void UINILibrary::TrimBuffer(char* Buffer)
{
	char* CharPtr;

	for (CharPtr = Buffer; CharPtr[1] != '\0'; CharPtr++);

	while (*CharPtr == ' ' || *CharPtr == '\t')
	{
		*CharPtr = '\0';
		CharPtr--;
	}
}