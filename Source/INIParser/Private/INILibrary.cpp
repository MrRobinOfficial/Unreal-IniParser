// Copyright 2023 MrRobin. All Rights Reserved.

#include "IniLibrary.h"
#include "Kismet/KismetStringLibrary.h"

static const char& COMMENT_CHAR = ';';
static const char& SECTION_START_CHAR = '[';
static const char& SECTION_END_CHAR = ']';
static const char& TAB_CHAR = '\t';
static const char& NEWLINE_CHAR = '\n';
static const char& SPACE_CHAR = ' ';
static const char& EMPTY_CHAR = '\0';
static const char& EQUALS_CHAR = '=';

FIniData UIniLibrary::ParseIniString(FString String)
{
	FIniData Result = FIniData();

	char Buffer[256];
	*Buffer = EMPTY_CHAR;

	char CurrentSection[256];
	*CurrentSection = EMPTY_CHAR;

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

	for (auto It = String.CreateConstIterator(); It; ++It)
	{
		if (!String.IsValidIndex(It.GetIndex()))
			continue;

		char Char = String[It.GetIndex()];

		switch (State)
		{
			// Waiting for .ini data
			case 0:
				switch (Char)
				{
					case COMMENT_CHAR:
						State = 1; // Start comment
						break;

					case SECTION_START_CHAR:
						State = 2; // Start section name
						break;

					// Valid spacings
					case SPACE_CHAR:
					case NEWLINE_CHAR:
					case TAB_CHAR:
						break;

					default:
						AppendBuffer(Buffer, Char);
						State = 3; // Start key
						break;
				}
				break;

			// Reading comment
			case 1:
				if (Char == NEWLINE_CHAR) State = 0; // End comment
				break;

			// Section name started
			case 2:
				switch (Char)
				{
					// End section name
					case SECTION_END_CHAR:
						strcpy_s(CurrentSection, 256, Buffer);
						*Buffer = EMPTY_CHAR;
						State = 0;
						break;

					// Invalid section name (discard)
					case NEWLINE_CHAR:
						*Buffer = EMPTY_CHAR;
						State = 0;
						break;

					default:
						AppendBuffer(Buffer, Char);
						break;
				}
				break;

			// Key started
			case 3:
				switch (Char)
				{
					case SPACE_CHAR:
					case TAB_CHAR:
						strcpy_s(CurrentKey, 256, Buffer);
						*Buffer = EMPTY_CHAR;
						State = 4; // End key
						break;

					// Invalid key (discard)
					case NEWLINE_CHAR:
						State = 0;
						break;

					default:
						AppendBuffer(Buffer, Char);
						break;
				}		
				break;

			// End of key
			case 4:
				switch (Char)
				{
					case EQUALS_CHAR:
						State = 5; // Ready for value
						break;

					case NEWLINE_CHAR:
						State = 0; // Invalid key value
						break;

					case SPACE_CHAR:
					case TAB_CHAR:
						break;

					default:
						State = 7; // Invalid key format
						break;
				}
				break;

			// Ready for value
			case 5:
				switch (Char)
				{
					case NEWLINE_CHAR:
						State = 0; // Invalid key value
						break;

					case SPACE_CHAR:
					case TAB_CHAR:
						break;

					default:
						AppendBuffer(Buffer, Char);
						State = 6; // Begin value
						break;
				}
				break;

			// Start of value
			case 6:
				if (Char == NEWLINE_CHAR)
				{
					TrimBuffer(Buffer);
					strcpy_s(CurrentValue, 256, Buffer);
					*Buffer = EMPTY_CHAR;
					State = 0;

					FIniSection& Section = Result.AddSection(CurrentSection);
					Section.AddProperty(CurrentKey, CurrentValue);
				}
				else
					AppendBuffer(Buffer, Char);
				break;

			// Invalid key format
			case 7:
				if (Char == NEWLINE_CHAR) State = 0;
				break;
		}
	}

	return Result;
}

void UIniLibrary::AppendBuffer(char* Buffer, char Char)
{
	if (iscntrl(Char))
		return;

	char str[2] = { Char, EMPTY_CHAR };
	strcat_s(Buffer, 256, str);
}

void UIniLibrary::TrimBuffer(char* Buffer)
{
	char* Char = &Buffer[strlen(Buffer) - 1];

	if (*Char == SPACE_CHAR || *Char == TAB_CHAR)
	{
		*Char = EMPTY_CHAR;
		TrimBuffer(Buffer);
	}
}

FIniData UIniLibrary::MakeIniDataStruct(
	TMap<FString, FIniSection> Sections)
{
	return FIniData(Sections);
}

FString UIniLibrary::Conv_IniDataToString(const FIniData& Data) { return Data.ToString(); }

void UIniLibrary::GetSection(FIniData& Data, FString SectionName, FIniSection& OutSection)
{
	OutSection = Data.GetSection(SectionName);
}

bool UIniLibrary::GetTrySection(FIniData& Data, FString SectionName, FIniSection& OutSection)
{
	return Data.TryGetSection(SectionName, OutSection);
}

void UIniLibrary::GetProperty(FIniSection& Section, FString PropertyName, FIniProperty& OutProperty)
{
	OutProperty = Section.GetProperty(PropertyName);
}

bool UIniLibrary::GetTryProperty(FIniSection& Section, FString PropertyName, FIniProperty& OutProperty)
{
	return Section.TryGetProperty(PropertyName, OutProperty);
}

void UIniLibrary::GetValueAsInt32(FIniProperty& Property, int32& Value)
{
	Value = UKismetStringLibrary::Conv_StringToInt(Property.GetValue());
}

void UIniLibrary::GetValueAsInt64(FIniProperty& Property, int64& Value)
{
	Value = UKismetStringLibrary::Conv_StringToInt64(Property.GetValue());
}

void UIniLibrary::GetValueAsBoolean(FIniProperty& Property, bool& Value)
{
	Value = Property.GetValue().ToBool();
}

void UIniLibrary::GetValueAsDouble(FIniProperty& Property, double& Value)
{
	Value = UKismetStringLibrary::Conv_StringToDouble(Property.GetValue());
}

void UIniLibrary::GetValueAsFloat(FIniProperty& Property, float& Value)
{
	Value = UKismetStringLibrary::Conv_StringToDouble(Property.GetValue());
}

void UIniLibrary::GetValueAsVector(FIniProperty& Property, FVector& Value, bool& OutIsValid)
{
	UKismetStringLibrary::Conv_StringToVector(Property.GetValue(), Value, OutIsValid);
}

void UIniLibrary::GetValueAsVector3f(FIniProperty& Property, FVector3f& Value, bool& OutIsValid)
{
	UKismetStringLibrary::Conv_StringToVector3f(Property.GetValue(), Value, OutIsValid);
}

void UIniLibrary::GetValueAsVector2D(FIniProperty& Property, FVector2D& Value, bool& OutIsValid)
{
	UKismetStringLibrary::Conv_StringToVector2D(Property.GetValue(), Value, OutIsValid);
}

void UIniLibrary::GetValueAsRotator(FIniProperty& Property, FRotator& Value, bool& OutIsValid)
{
	UKismetStringLibrary::Conv_StringToRotator(Property.GetValue(), Value, OutIsValid);
}

void UIniLibrary::GetValueAsName(FIniProperty& Property, FName& Value)
{
	Value = UKismetStringLibrary::Conv_StringToName(Property.GetValue());
}

void UIniLibrary::GetValueAsString(FIniProperty& Property, FString& Value)
{
	Value = Property.GetValue();
}

void UIniLibrary::GetValueAsText(FIniProperty& Property, FText& Value)
{
	Value = FText::FromString(Property.GetValue());
}

void UIniLibrary::GetValueAsLinearColor(FIniProperty& Property, FLinearColor& Value, bool& OutIsValid)
{
	UKismetStringLibrary::Conv_StringToColor(Property.GetValue(), Value, OutIsValid);
}

void UIniLibrary::GetSections(FIniData& Data, TArray<FIniSection>& OutArray)
{
	Data.GetSections().GenerateValueArray(OutArray);
}

void UIniLibrary::GetProperties(FIniSection& Section, TArray<FIniProperty>& OutArray)
{
	Section.GetProperties().GenerateValueArray(OutArray);
}