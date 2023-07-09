#include "IniProperty.h"
#include "Kismet/KismetStringLibrary.h"

FString FIniProperty::ToString() const { return FString::Printf(TEXT("%s=%s"), *KeyName.ToString(), *Value); }

void FIniProperty::operator=(const uint8_t& NewValue) { Value = UKismetStringLibrary::Conv_ByteToString(NewValue); }
void FIniProperty::operator=(const int32& NewValue) { Value = UKismetStringLibrary::Conv_IntToString(NewValue); }
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
