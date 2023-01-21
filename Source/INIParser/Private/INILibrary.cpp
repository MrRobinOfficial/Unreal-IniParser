// Copyright 2023 MrRobin. All Rights Reserved.

#include "INILibrary.h"
#include "Kismet/KismetStringLibrary.h"

static const char& COMMENT_CHAR = ';';
static const char& SECTION_START_CHAR = '[';
static const char& SECTION_END_CHAR = ']';
static const char& TAB_CHAR = '\t';
static const char& NEWLINE_CHAR = '\n';
static const char& SPACE_CHAR = ' ';
static const char& EMPTY_CHAR = '\0';
static const char& EQUALS_CHAR = '=';

static PropertyCollection EMPTY_PROPERTIES = PropertyCollection();
static SectionCollection EMPTY_SECTIONS = SectionCollection();
static FIniProperty EMPTY_PROPERTY = FIniProperty();
static FIniSection EMPTY_SECTION = FIniSection();

FIniData UINILibrary::ParseIniFile(FString ParseString)
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

	for (auto It = ParseString.CreateConstIterator(); It; ++It)
	{
		if (!ParseString.IsValidIndex(It.GetIndex()))
			continue;

		char Char = ParseString[It.GetIndex()];

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

					FIniSection& Section = Result.FindOrAddSectionByName(CurrentSection);
					Section.AddProperty(FIniProperty(CurrentKey, CurrentValue));
					
					//if (Result.TryFindOrAddSectionByName(CurrentSection, Section))
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

FIniData UINILibrary::MakeIniDataStruct(
	TMap<FString, FIniSection> Sections,
	TMap<FString, FIniProperty> Properties)
{
	/*return FIniData(Sections, Properties);*/

	return FIniData();
}

FString UINILibrary::Conv_IniDataToString(const FIniData& Data) { return Data.ToString(); }

void UINILibrary::AppendBuffer(char* Buffer, char Char)
{
	char str[2] = { Char, EMPTY_CHAR };
	strcat_s(Buffer, 256, str);
}

void UINILibrary::TrimBuffer(char* Buffer)
{
	char* Char = &Buffer[strlen(Buffer) - 1];

	if (*Char == SPACE_CHAR || *Char == TAB_CHAR)
	{
		*Char = EMPTY_CHAR;
		TrimBuffer(Buffer);
	}
}

void FIniData::AddSection(FIniSection Section, bool bOverwriteValueIfExist)
{
	if (Sections.Contains(Section.GetSectionName()) && !bOverwriteValueIfExist)
		return;

	Sections.Add(Section.GetSectionName(), Section);
}

bool FIniData::DoesSectionExist(const FString& Name) const { return Sections.Contains(Name); }

bool FIniData::TryFindSectionByName(FString Name, FIniSection*& OutSection)
{
	if (Name.IsEmpty())
		return false;

	OutSection = Sections.Find(Name);
	return OutSection != nullptr;
}

bool FIniData::TryFindOrAddSectionByName(FString Name, FIniSection& OutSection)
{
	if (Name.IsEmpty())
		return false;

	OutSection = Sections.FindOrAdd(Name, FIniSection(Name));
	return true;
}

FIniSection& FIniData::FindOrAddSectionByName(FString Name)
{
	return Sections.FindOrAdd(Name, FIniSection(Name));
}

void FIniSection::AddProperty(FIniProperty Property, bool bOverwriteValueIfExist)
{
	if (Properties.Contains(Property.GetKeyName()) && !bOverwriteValueIfExist)
		return;

	Properties.Add(Property.GetKeyName(), Property);
}

bool FIniSection::DoesPropertyExist(const FString& Name) const { return Properties.Contains(Name); }

bool FIniSection::TryFindPropertyByName(FString Name, FIniProperty*& OutProperty)
{
	OutProperty = nullptr;

	if (Name.IsEmpty())
		return false;

	OutProperty = Properties.Find(Name);
	return OutProperty != nullptr;
}

bool FIniSection::TryFindOrAddPropertyByName(FString Name, FIniProperty& OutProperty)
{
	if (Name.IsEmpty())
		return false;

	OutProperty = Properties.FindOrAdd(Name, FIniProperty(Name));
	return true;
}

FIniProperty& FIniSection::FindOrAddPropertyByName(FString Name)
{
	return Properties.FindOrAdd(Name, FIniProperty(Name));
}

FORCEINLINE FString FIniSection::ToString() const { return SectionName; }

FORCEINLINE FString FIniProperty::ToString() const { return FString::Printf(TEXT("%s=%s"), *KeyName, *Value); }

void FIniProperty::operator=(const uint8_t& NewValue) { Value = UKismetStringLibrary::Conv_ByteToString(NewValue); }
void FIniProperty::operator=(const int& NewValue) { Value = UKismetStringLibrary::Conv_IntToString(NewValue); }
void FIniProperty::operator=(const int64& NewValue) { Value = UKismetStringLibrary::Conv_Int64ToString(NewValue); }
void FIniProperty::operator=(const FIntPoint& NewValue) { Value = UKismetStringLibrary::Conv_IntPointToString(NewValue); }
void FIniProperty::operator=(const bool& NewValue) { Value = UKismetStringLibrary::Conv_BoolToString(NewValue); }
void FIniProperty::operator=(const double& NewValue) { Value = UKismetStringLibrary::Conv_DoubleToString(NewValue); }
void FIniProperty::operator=(const float& NewValue) { Value = FString::SanitizeFloat(NewValue); }
void FIniProperty::operator=(const FVector& NewValue) { Value = UKismetStringLibrary::Conv_VectorToString(NewValue); }
void FIniProperty::operator=(const FVector3f& NewValue) { Value = UKismetStringLibrary::Conv_Vector3fToString(NewValue); }
void FIniProperty::operator=(const FVector2D& NewValue) { Value = UKismetStringLibrary::Conv_Vector2dToString(NewValue); }
void FIniProperty::operator=(const FIntVector& NewValue) { Value = UKismetStringLibrary::Conv_IntVectorToString(NewValue); }
void FIniProperty::operator=(const FRotator& NewValue) { Value = UKismetStringLibrary::Conv_RotatorToString(NewValue); }
void FIniProperty::operator=(const FMatrix& NewValue) { Value = UKismetStringLibrary::Conv_MatrixToString(NewValue); }
void FIniProperty::operator=(const FName& NewValue) { Value = UKismetStringLibrary::Conv_NameToString(NewValue); }
void FIniProperty::operator=(const FString& NewValue) { Value = NewValue; }
void FIniProperty::operator=(const FText& NewValue) { Value = NewValue.ToString(); }
void FIniProperty::operator=(UObject* NewValue) { Value = UKismetStringLibrary::Conv_ObjectToString(NewValue); }
void FIniProperty::operator=(const FTransform& NewValue) { Value = UKismetStringLibrary::Conv_TransformToString(NewValue); }
void FIniProperty::operator=(const FLinearColor& NewValue) { Value = UKismetStringLibrary::Conv_ColorToString(NewValue); }
void FIniProperty::operator=(const FInputDeviceId& NewValue) { Value = UKismetStringLibrary::Conv_InputDeviceIdToString(NewValue); }
void FIniProperty::operator=(const FPlatformUserId& NewValue) { Value = UKismetStringLibrary::Conv_PlatformUserIdToString(NewValue); }

FIniProperty::operator FString() const { return GetValue(); }

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
	//if (!Sections.Contains(SectionName))
	//{
	//	if (false)
	//		Sections.Add(SectionName);
	//	else
	//		return EMPTY_SECTION;
	//}

	if (!Sections.Contains(SectionName))
		return EMPTY_SECTION;

	UE_LOG(LogTemp, Warning, TEXT("Works = %s"), *SectionName);

	return Sections[SectionName];
}

FIniProperty& FIniSection::operator[](const FString& PropertyName)
{
	//if (!Properties.Contains(PropertyName))
	//{
	//	// TODO: Add to map
	//	return EMPTY_PROPERTY;
	//}

	//if (!Properties.Contains(PropertyName))
	//	return EMPTY_PROPERTY;

	//UE_LOG(LogTemp, Warning, TEXT("Working = %s"), *PropertyName);

	//Properties[GetKeyName()]

	return Properties[PropertyName];
}

const FString UINILibrary::ReadValueAsStringFromIniData(
	FIniData& Data,
	FString SectionName,
	FString PropertyName)
{
	//if (!Data.DoesSectionExist(SectionName))
	//	return FString();

	//if (!Data[SectionName].DoesPropertyExist(PropertyName))
	//	return FString();

	return Data[SectionName][PropertyName];
}

void UINILibrary::WriteValueAsStringFromIniData(
	FIniData& Data,
	FString SectionName,
	FString PropertyName,
	FString NewValue)
{
	if (!Data.DoesSectionExist(SectionName))
		return;

	if (!Data[SectionName].DoesPropertyExist(PropertyName))
		return;

	Data[SectionName][PropertyName] = NewValue;
}

bool UINILibrary::TryGetSectionFromIniData(FIniData& Data, FString SectionName, FIniSection& OutSection)
{
	FIniSection* Ptr = nullptr;
	bool bResult = Data.TryFindSectionByName(SectionName, Ptr);

	OutSection = *Ptr;
	return bResult;
}

bool UINILibrary::TryGetPropertyFromIniSection(FIniSection& Section, FString PropertyName, FIniProperty& OutProperty)
{
	FIniProperty* Ptr = nullptr;
	bool bResult = Section.TryFindPropertyByName(PropertyName, Ptr);

	OutProperty = *Ptr;
	return bResult;
}

TArray<FIniProperty> UINILibrary::GetAllPropertiesFromIniData(FIniData& Data, FString PropertyName)
{
	// TODO: Get all properties as TArray<FIniProperty> (casting from TMap)

	return TArray<FIniProperty>();
}