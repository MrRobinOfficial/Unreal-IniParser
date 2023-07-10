// Copyright 2023 MrRobin. All Rights Reserved.

#include "IniLibrary.h"
#include "Kismet/KismetStringLibrary.h"

DEFINE_LOG_CATEGORY(LogIniParser);

static const char& COMMENT_CHAR = ';';
static const char& SECTION_START_CHAR = '[';
static const char& SECTION_END_CHAR = ']';
static const char& DOUBLE_QUOTE_CHAR = '\"';
static const char& APOSTROPHE_CHAR = '\'';
static const char& TAB_CHAR = '\t';
static const char& NEWLINE_CHAR = '\n';
static const char& SPACE_CHAR = ' ';
static const char& EMPTY_CHAR = '\0';
static const char& EQUALS_CHAR = '=';

void UIniLibrary::AppendBuffer(char* Buffer, char Char)
{
	if (iscntrl(Char)) // Check if character is a control character
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

FIniData UIniLibrary::ParseIniFromString(FString String)
{
	FIniData GlobalData;

	char Buffer[256] = { EMPTY_CHAR };
	char CurrentSection[256] = { EMPTY_CHAR };
	char CurrentKey[256];
	char CurrentValue[256];
	char CurrentComment[256];

	enum class ParserState
	{
		ReadyForIniData,
		CommentStarted,
		SectionNameStarted,
		KeyStarted,
		KeyFinished,
		ReadyForValue,
		ValueStarted,
		InvalidKeyFormat
	};

	ParserState State = ParserState::ReadyForIniData;

	for (TCHAR Char : String)
	{
		switch (State)
		{
			case ParserState::ReadyForIniData:
				switch (Char)
				{
					case COMMENT_CHAR:
						State = ParserState::CommentStarted;
						continue;

					case SECTION_START_CHAR:
						State = ParserState::SectionNameStarted;
						break;

					case SPACE_CHAR:
					case NEWLINE_CHAR:
					case TAB_CHAR:
						break;

					default:
						AppendBuffer(Buffer, Char);
						State = ParserState::KeyStarted;
						break;
				}
				break;

			case ParserState::CommentStarted:
				if (Char == NEWLINE_CHAR)
				{
					TrimBuffer(Buffer);
					strcpy_s(CurrentComment, Buffer);
					Buffer[0] = EMPTY_CHAR;

					State = ParserState::ReadyForIniData;

					if (CurrentSection[0] == EMPTY_CHAR)
						GlobalData.AddComment(CurrentComment);
					else
					{
						FIniSection& Section = GlobalData.FindOrAddSection(FName(CurrentSection));
						Section.AddComment(CurrentComment);
					}
				}
				else
					AppendBuffer(Buffer, Char);
				break;

			case ParserState::SectionNameStarted:
				switch (Char)
				{
					case SECTION_END_CHAR:
						strcpy_s(CurrentSection, Buffer);
						Buffer[0] = EMPTY_CHAR;
						State = ParserState::ReadyForIniData;
						break;

					case NEWLINE_CHAR:
						Buffer[0] = EMPTY_CHAR;
						State = ParserState::ReadyForIniData;
						break;

					default:
						AppendBuffer(Buffer, Char);
						break;
				}
				break;

			case ParserState::KeyStarted:
				switch (Char)
				{
					case SPACE_CHAR:
					case TAB_CHAR:
						strcpy_s(CurrentKey, Buffer);
						Buffer[0] = EMPTY_CHAR;
						State = ParserState::KeyFinished;
						break;

					case NEWLINE_CHAR:
						State = ParserState::ReadyForIniData;
						break;

					default:
						AppendBuffer(Buffer, Char);
						break;
				}
				break;

			case ParserState::KeyFinished:
				switch (Char)
				{
					case EQUALS_CHAR:
						State = ParserState::ReadyForValue;
						break;

					case NEWLINE_CHAR:
						State = ParserState::ReadyForIniData;
						break;

					case SPACE_CHAR:
					case TAB_CHAR:
						break;

					default:
						State = ParserState::InvalidKeyFormat;
						break;
				}
				break;

			case ParserState::ReadyForValue:
				switch (Char)
				{
					case NEWLINE_CHAR:
						State = ParserState::ReadyForIniData;
						break;

					case SPACE_CHAR:
					case TAB_CHAR:
						break;

					default:
						if (Char != DOUBLE_QUOTE_CHAR && Char != APOSTROPHE_CHAR)
							AppendBuffer(Buffer, Char);

						State = ParserState::ValueStarted;
						break;
				}
				break;

			case ParserState::ValueStarted:
				switch (Char)
				{
					case NEWLINE_CHAR:
					{
						TrimBuffer(Buffer);
						strcpy_s(CurrentValue, Buffer);
						Buffer[0] = EMPTY_CHAR;
						State = ParserState::ReadyForIniData;

						if (CurrentSection[0] == EMPTY_CHAR)
							GlobalData.FindOrAddProperty(FName(CurrentKey), CurrentValue);
						else
						{
							FIniSection& Section = GlobalData.FindOrAddSection(FName(CurrentSection));
							Section.FindOrAddProperty(FName(CurrentKey), CurrentValue);
						}
					}
					break;

					case DOUBLE_QUOTE_CHAR:
					case APOSTROPHE_CHAR:
						break;

					default:
						AppendBuffer(Buffer, Char);
						break;
				}
				break;

			case ParserState::InvalidKeyFormat:
				if (Char == NEWLINE_CHAR)
					State = ParserState::ReadyForIniData;
				break;
			}
	}

	if (State == ParserState::ValueStarted)
	{
		TrimBuffer(Buffer);
		strcpy_s(CurrentValue, Buffer);
		Buffer[0] = EMPTY_CHAR;
		State = ParserState::ReadyForIniData;

		FIniSection& Section = GlobalData.FindOrAddSection(FName(CurrentSection));
		Section.AddProperty(FName(CurrentKey), CurrentValue);
	}

	return GlobalData;
}

FIniData UIniLibrary::ParseIniFromFile(FString FilePath)
{
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	FString Contents;

	if (FileManager.FileExists(*FilePath))
	{
		if (FFileHelper::LoadFileToString(Contents, *FilePath, FFileHelper::EHashOptions::None))
			return ParseIniFromString(Contents);
	}
	else
	{
		UE_LOG(LogIniParser, Warning, TEXT("ERROR: Can not read the file because it was not found."));
		UE_LOG(LogIniParser, Warning, TEXT("Expected file location: %s"), *FilePath);
	}

	return FIniData();
}

FIniData UIniLibrary::MakeIniDataStruct(
	TMap<FName, FIniSection> Sections)
{
	return FIniData(Sections);
}

FString UIniLibrary::Conv_IniDataToString(const FIniData& Data) { return Data.ToString(); }

void UIniLibrary::GetSection(FIniData& Data, FName SectionName, FIniSection& OutSection)
{
	OutSection = Data.GetSection(SectionName);
}

bool UIniLibrary::GetTrySection(FIniData& Data, FName SectionName, FIniSection& OutSection)
{
	if (Data.HasEmptySections())
		return false;

	return Data.TryGetSection(SectionName, OutSection);
}

void UIniLibrary::GetProperty(FIniSection& Section, FName PropertyName, FIniProperty& OutProperty)
{
	OutProperty = Section.GetProperty(PropertyName);
}

bool UIniLibrary::GetTryProperty(FIniSection& Section, FName PropertyName, FIniProperty& OutProperty)
{
	if (Section.HasEmptyProperties())
		return false;

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