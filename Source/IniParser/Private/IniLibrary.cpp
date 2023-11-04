// Copyright 2023 MrRobin. All Rights Reserved.

#include "IniLibrary.h"

#include "IniParserModule.h"

#include "Kismet/KismetStringLibrary.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "GenericPlatform/GenericPlatformFile.h"

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

FString UIniLibrary::ParseIniToString(const FIniData& Data)
{
	FStringBuilderBase Builder;

	// Global comments
	for (const auto& Comment : Data.GetComments())
	{
		Builder.AppendChar(COMMENT_CHAR);
		Builder.AppendChar(SPACE_CHAR);
		Builder.Append(Comment);
		Builder.AppendChar(NEWLINE_CHAR);
	}

	// Global properties
	for (const auto& PropertyPair : Data.GetProperties())
	{
		const FIniProperty& Property = PropertyPair.Value;

		Builder.Append(PropertyPair.Key.ToString());
		Builder.AppendChar(SPACE_CHAR);
		Builder.AppendChar(EQUALS_CHAR);
		Builder.AppendChar(SPACE_CHAR);
		Builder.Append(Property.GetValueReadableString());
		Builder.AppendChar(NEWLINE_CHAR);
	}

	if (Builder.Len() > 0)
		Builder.AppendChar(NEWLINE_CHAR);

	int32 NumOfSections = Data.GetNumOfSections();

	for (const auto& SectionPair : Data.GetSections())
	{
		const FIniSection& Section = SectionPair.Value;

		Builder.AppendChar(SECTION_START_CHAR);
		Builder.Append(SectionPair.Key.ToString());
		Builder.AppendChar(SECTION_END_CHAR);
		Builder.AppendChar(NEWLINE_CHAR);

		for (const auto& Comment : Section.GetComments())
		{
			Builder.AppendChar(COMMENT_CHAR);
			Builder.AppendChar(SPACE_CHAR);
			Builder.Append(Comment);
			Builder.AppendChar(NEWLINE_CHAR);
		}

		int32 NumOfProperties = Section.GetNumOfProperties();

		for (const auto& PropertyPair : Section.GetProperties())
		{
			const FIniProperty& Property = PropertyPair.Value;

			Builder.Append(PropertyPair.Key.ToString());
			Builder.AppendChar(SPACE_CHAR);
			Builder.AppendChar(EQUALS_CHAR);
			Builder.AppendChar(SPACE_CHAR);
			Builder.Append(Property.GetValueReadableString());

			NumOfProperties--;

			if (NumOfProperties >= 1)
				Builder.AppendChar(NEWLINE_CHAR);
		}

		NumOfSections--;

		if (NumOfSections >= 1)
		{
			Builder.AppendChar(NEWLINE_CHAR);
			Builder.AppendChar(NEWLINE_CHAR);
		}
	}

	return Builder.ToString();
}

FIniData UIniLibrary::ReadIniFromFile(FString FilePath)
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

void UIniLibrary::WriteIniToFile(FString FilePath, const FIniData& Data)
{
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	FString Contents;

	FString Directory = FPaths::GetPath(FilePath);

	if (!FPaths::DirectoryExists(*Directory))
		FileManager.CreateDirectoryTree(*Directory);

	FFileHelper::SaveStringToFile(ParseIniToString(Data), *FilePath);
}

FIniData UIniLibrary::MakeIniData(TMap<FName, FIniSection> Sections)
{
	return FIniData(Sections);
}

FIniSection UIniLibrary::MakeIniSection(TMap<FName, FIniProperty> Properties)
{
	return FIniSection(Properties);
}

FString UIniLibrary::Conv_IniDataToString(const FIniData& Data)
{
	return ParseIniToString(Data);
}

int32 UIniLibrary::GetNumOfSections(FIniData& Data)
{
	return Data.GetNumOfSections();
}

int32 UIniLibrary::GetNumOfGlobalProperties(FIniData& Data)
{
	return Data.GetNumOfProperties();
}

int32 UIniLibrary::GetNumOfGlobalComments(FIniData& Data)
{
	return Data.GetNumOfComments();
}

int32 UIniLibrary::GetNumOfComments(FIniData& Data, FName SectionName)
{
	auto& Sect = Data.GetSection(SectionName);
	return Sect.GetNumOfProperties();
}

int32 UIniLibrary::GetNumOfProperties(FIniData& Data, FName SectionName)
{
	auto& Sect = Data.GetSection(SectionName);
	return Sect.GetNumOfProperties();
}

void UIniLibrary::GetComments(FIniData& Data, FName SectionName, TArray<FString>& OutArray)
{
	auto& Sect = Data.GetSection(SectionName);
	OutArray = Sect.GetComments();
}

void UIniLibrary::GetGlobalComments(FIniData& Data, TArray<FString>& OutArray)
{
	OutArray = Data.GetComments();
}

#pragma region Global Property Getters/Setters

void UIniLibrary::GetPropertyValueAsInt(FIniData& Data, FName SectionName, FName PropertyName, int32& OutValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.GetValueAsInt(OutValue);
}

void UIniLibrary::GetPropertyValueAsInt64(FIniData& Data, FName SectionName, FName PropertyName, int64& OutValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.GetValueAsInt64(OutValue);
}

void UIniLibrary::GetPropertyValueAsBoolean(FIniData& Data, FName SectionName, FName PropertyName, bool& OutValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.GetValueAsBoolean(OutValue);
}

void UIniLibrary::GetPropertyValueAsFloat(FIniData& Data, FName SectionName, FName PropertyName, float& OutValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.GetValueAsFloat(OutValue);
}

void UIniLibrary::GetPropertyValueAsDouble(FIniData& Data, FName SectionName, FName PropertyName, double& OutValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.GetValueAsDouble(OutValue);
}

void UIniLibrary::GetPropertyValueAsVector(FIniData& Data, FName SectionName, FName PropertyName, FVector& OutConvertedVector, bool& OutIsValid)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.GetValueAsVector(OutConvertedVector, OutIsValid);
}

void UIniLibrary::GetPropertyValueAsVector3f(FIniData& Data, FName SectionName, FName PropertyName, FVector3f& OutConvertedVector, bool& OutIsValid)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.GetValueAsVector3f(OutConvertedVector, OutIsValid);
}

void UIniLibrary::GetPropertyValueAsVector2D(FIniData& Data, FName SectionName, FName PropertyName, FVector2D& OutConvertedVector2D, bool& OutIsValid)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.GetValueAsVector2D(OutConvertedVector2D, OutIsValid);
}

void UIniLibrary::GetPropertyValueAsRotator(FIniData& Data, FName SectionName, FName PropertyName, FRotator& OutConvertedRotator, bool& OutIsValid)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.GetValueAsRotator(OutConvertedRotator, OutIsValid);
}

void UIniLibrary::GetPropertyValueAsLinearColor(FIniData& Data, FName SectionName, FName PropertyName, FLinearColor& OutConvertedColor, bool& OutIsValid)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.GetValueAsColor(OutConvertedColor, OutIsValid);
}

void UIniLibrary::GetPropertyValueAsName(FIniData& Data, FName SectionName, FName PropertyName, FName& OutValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	OutValue = Prop.GetValueAsName();
}

void UIniLibrary::GetPropertyValueAsText(FIniData& Data, FName SectionName, FName PropertyName, FText& OutValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	OutValue = FText::FromString(Prop.GetValueAsRawString());
}

void UIniLibrary::GetPropertyValueAsString(FIniData& Data, FName SectionName, FName PropertyName, FString& OutValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	OutValue = Prop.GetValueAsRawString();
}

void UIniLibrary::SetPropertyValueAsString(FIniData& Data, FName SectionName, FName PropertyName, FString NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsString(NewValue);
}

void UIniLibrary::SetPropertyValueAsText(FIniData& Data, FName SectionName, FName PropertyName, FText NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsText(NewValue);
}

void UIniLibrary::SetPropertyValueAsName(FIniData& Data, FName SectionName, FName PropertyName, FName NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsName(NewValue);
}

void UIniLibrary::SetPropertyValueAsObject(FIniData& Data, FName SectionName, FName PropertyName, UObject* NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsObject(NewValue);
}

void UIniLibrary::SetPropertyValueAsByte(FIniData& Data, FName SectionName, FName PropertyName, uint8 NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsByte(NewValue);
}

void UIniLibrary::SetPropertyValueAsInt(FIniData& Data, FName SectionName, FName PropertyName, int32 NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsInt(NewValue);
}

void UIniLibrary::SetPropertyValueAsInt64(FIniData& Data, FName SectionName, FName PropertyName, int64 NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsInt64(NewValue);
}

void UIniLibrary::SetPropertyValueAsIntPoint(FIniData& Data, FName SectionName, FName PropertyName, FIntPoint NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsIntPoint(NewValue);
}

void UIniLibrary::SetPropertyValueAsBool(FIniData& Data, FName SectionName, FName PropertyName, bool bNewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsBoolean(bNewValue);
}

void UIniLibrary::SetPropertyValueAsFloat(FIniData& Data, FName SectionName, FName PropertyName, float NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsFloat(NewValue);
}

void UIniLibrary::SetPropertyValueAsDouble(FIniData& Data, FName SectionName, FName PropertyName, double NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsDouble(NewValue);
}

void UIniLibrary::SetPropertyValueAsVector(FIniData& Data, FName SectionName, FName PropertyName, FVector NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsVector(NewValue);
}

void UIniLibrary::SetPropertyValueAsVector2D(FIniData& Data, FName SectionName, FName PropertyName, FVector2D NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsVector2D(NewValue);
}

void UIniLibrary::SetPropertyValueAsVector3f(FIniData& Data, FName SectionName, FName PropertyName, FVector3f NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsVector3f(NewValue);
}

void UIniLibrary::SetPropertyValueAsIntVector(FIniData& Data, FName SectionName, FName PropertyName, FIntVector NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsIntVector(NewValue);
}

void UIniLibrary::SetPropertyValueAsRotator(FIniData& Data, FName SectionName, FName PropertyName, FRotator NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsRotator(NewValue);
}

void UIniLibrary::SetPropertyValueAsMatrix(FIniData& Data, FName SectionName, FName PropertyName, FMatrix NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsMatrix(NewValue);
}

void UIniLibrary::SetPropertyValueAsTransform(FIniData& Data, FName SectionName, FName PropertyName, FTransform NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsTransform(NewValue);
}

void UIniLibrary::SetPropertyValueAsLinearColor(FIniData& Data, FName SectionName, FName PropertyName, FLinearColor NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsColor(NewValue);
}

void UIniLibrary::SetPropertyValueAsInputDeviceId(FIniData& Data, FName SectionName, FName PropertyName, FInputDeviceId NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsInputDeviceId(NewValue);
}

void UIniLibrary::SetPropertyValueAsPlatformUserId(FIniData& Data, FName SectionName, FName PropertyName, FPlatformUserId NewValue)
{
	auto& Sect = Data.GetSection(SectionName);
	auto& Prop = Sect.GetProperty(PropertyName);
	Prop.SetValueAsPlatformUserId(NewValue);
}

#pragma endregion

#pragma region Property Getters/Setters

void UIniLibrary::GetGlobalPropertyValueAsInt(FIniData& Data, FName PropertyName, int32& OutValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.GetValueAsInt(OutValue);
}

void UIniLibrary::GetGlobalPropertyValueAsInt64(FIniData& Data, FName PropertyName, int64& OutValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.GetValueAsInt64(OutValue);
}

void UIniLibrary::GetGlobalPropertyValueAsBoolean(FIniData& Data, FName PropertyName, bool& OutValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.GetValueAsBoolean(OutValue);
}

void UIniLibrary::GetGlobalPropertyValueAsFloat(FIniData& Data, FName PropertyName, float& OutValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.GetValueAsFloat(OutValue);
}

void UIniLibrary::GetGlobalPropertyValueAsDouble(FIniData& Data, FName PropertyName, double& OutValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.GetValueAsDouble(OutValue);
}

void UIniLibrary::GetGlobalPropertyValueAsVector(FIniData& Data, FName PropertyName, FVector& OutConvertedVector, bool& OutIsValid)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.GetValueAsVector(OutConvertedVector, OutIsValid);
}

void UIniLibrary::GetGlobalPropertyValueAsVector3f(FIniData& Data, FName PropertyName, FVector3f& OutConvertedVector, bool& OutIsValid)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.GetValueAsVector3f(OutConvertedVector, OutIsValid);
}

void UIniLibrary::GetGlobalPropertyValueAsVector2D(FIniData& Data, FName PropertyName, FVector2D& OutConvertedVector2D, bool& OutIsValid)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.GetValueAsVector2D(OutConvertedVector2D, OutIsValid);
}

void UIniLibrary::GetGlobalPropertyValueAsRotator(FIniData& Data, FName PropertyName, FRotator& OutConvertedRotator, bool& OutIsValid)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.GetValueAsRotator(OutConvertedRotator, OutIsValid);
}

void UIniLibrary::GetGlobalPropertyValueAsLinearColor(FIniData& Data, FName PropertyName, FLinearColor& OutConvertedColor, bool& OutIsValid)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.GetValueAsColor(OutConvertedColor, OutIsValid);
}

void UIniLibrary::GetGlobalPropertyValueAsName(FIniData& Data, FName PropertyName, FName& OutValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	OutValue = Prop.GetValueAsName();
}

void UIniLibrary::GetGlobalPropertyValueAsText(FIniData& Data, FName PropertyName, FText& OutValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	OutValue = FText::FromString(Prop.GetValueAsRawString());
}

void UIniLibrary::GetGlobalPropertyValueAsString(FIniData& Data, FName PropertyName, FString& OutValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	OutValue = Prop.GetValueAsRawString();
}

void UIniLibrary::SetGlobalPropertyValueAsString(FIniData& Data, FName PropertyName, FString NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsString(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsText(FIniData& Data, FName PropertyName, FText NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsText(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsName(FIniData& Data, FName PropertyName, FName NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsName(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsObject(FIniData& Data, FName PropertyName, UObject* NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsObject(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsByte(FIniData& Data, FName PropertyName, uint8 NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsByte(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsInt(FIniData& Data, FName PropertyName, int32 NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsInt(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsInt64(FIniData& Data, FName PropertyName, int64 NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsInt64(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsIntPoint(FIniData& Data, FName PropertyName, FIntPoint NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsIntPoint(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsBool(FIniData& Data, FName PropertyName, bool bNewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsBoolean(bNewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsFloat(FIniData& Data, FName PropertyName, float NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsFloat(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsDouble(FIniData& Data, FName PropertyName, double NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsDouble(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsVector(FIniData& Data, FName PropertyName, FVector NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsVector(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsVector2D(FIniData& Data, FName PropertyName, FVector2D NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsVector2D(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsVector3f(FIniData& Data, FName PropertyName, FVector3f NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsVector3f(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsIntVector(FIniData& Data, FName PropertyName, FIntVector NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsIntVector(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsRotator(FIniData& Data, FName PropertyName, FRotator NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsRotator(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsMatrix(FIniData& Data, FName PropertyName, FMatrix NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsMatrix(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsTransform(FIniData& Data, FName PropertyName, FTransform NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsTransform(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsLinearColor(FIniData& Data, FName PropertyName, FLinearColor NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsColor(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsInputDeviceId(FIniData& Data, FName PropertyName, FInputDeviceId NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsInputDeviceId(NewValue);
}

void UIniLibrary::SetGlobalPropertyValueAsPlatformUserId(FIniData& Data, FName PropertyName, FPlatformUserId NewValue)
{
	auto& Prop = Data.GetProperty(PropertyName);
	Prop.SetValueAsPlatformUserId(NewValue);
}

#pragma endregion