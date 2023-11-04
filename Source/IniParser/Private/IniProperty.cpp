// Copyright 2023 MrRobin. All Rights Reserved.

#include "IniProperty.h"

#include "IniParserModule.h"

void FIniProperty::SetValueAsString(FString NewValue)
{
	Value = Stringfy(NewValue);
}

void FIniProperty::SetValueAsText(FText NewValue)
{
	Value = Stringfy(NewValue.ToString());
}

void FIniProperty::SetValueAsName(FName NewValue)
{
	Value = Stringfy(UKismetStringLibrary::Conv_NameToString(NewValue));
}

void FIniProperty::SetValueAsObject(UObject* NewValue)
{
	Value = Stringfy(UKismetStringLibrary::Conv_ObjectToString(NewValue));
}

void FIniProperty::SetValueAsByte(uint8 NewValue)
{
	Value = UKismetStringLibrary::Conv_ByteToString(NewValue);
}

void FIniProperty::SetValueAsInt(int32 NewValue)
{
	Value = UKismetStringLibrary::Conv_IntToString(NewValue);
}

void FIniProperty::SetValueAsInt64(int64 NewValue)
{
	Value = UKismetStringLibrary::Conv_Int64ToString(NewValue);
}

void FIniProperty::SetValueAsIntPoint(FIntPoint NewValue)
{
	Value = UKismetStringLibrary::Conv_IntPointToString(NewValue);
}

void FIniProperty::SetValueAsBoolean(bool bNewValue)
{
	Value = UKismetStringLibrary::Conv_BoolToString(bNewValue);
}

void FIniProperty::SetValueAsFloat(float NewValue)
{
	Value = FString::SanitizeFloat(NewValue);
}

void FIniProperty::SetValueAsDouble(double NewValue)
{
	Value = FString::SanitizeFloat(NewValue);
}

void FIniProperty::SetValueAsVector(FVector NewValue)
{
	Value = UKismetStringLibrary::Conv_VectorToString(NewValue);
}

void FIniProperty::SetValueAsVector2D(FVector2D NewValue)
{
	Value = UKismetStringLibrary::Conv_Vector2dToString(NewValue);
}

void FIniProperty::SetValueAsVector3f(FVector3f NewValue)
{
	Value = UKismetStringLibrary::Conv_Vector3fToString(NewValue);
}

void FIniProperty::SetValueAsIntVector(FIntVector NewValue)
{
	Value = UKismetStringLibrary::Conv_IntVectorToString(NewValue);
}

void FIniProperty::SetValueAsRotator(FRotator NewValue)
{
	Value = UKismetStringLibrary::Conv_RotatorToString(NewValue);
}

void FIniProperty::SetValueAsMatrix(FMatrix NewValue)
{
	Value = UKismetStringLibrary::Conv_MatrixToString(NewValue);
}

void FIniProperty::SetValueAsTransform(FTransform NewValue)
{
	Value = UKismetStringLibrary::Conv_TransformToString(NewValue);
}

void FIniProperty::SetValueAsColor(FLinearColor NewValue)
{
	Value = UKismetStringLibrary::Conv_ColorToString(NewValue);
}

void FIniProperty::SetValueAsInputDeviceId(FInputDeviceId NewValue)
{
	Value = UKismetStringLibrary::Conv_InputDeviceIdToString(NewValue);
}

void FIniProperty::SetValueAsPlatformUserId(FPlatformUserId NewValue)
{
	Value = UKismetStringLibrary::Conv_PlatformUserIdToString(NewValue);
}