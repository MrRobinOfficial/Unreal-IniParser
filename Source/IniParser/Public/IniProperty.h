// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IniProperty.generated.h"

USTRUCT(BlueprintType)
struct FIniProperty
{
	GENERATED_BODY()

public:
	const FString& GetKeyName() const { return KeyName; }

	const FString& GetValue() const { return Value; }

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="IniProperty")
	FString KeyName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IniProperty")
	FString Value;

public:
	FIniProperty()
	{
		KeyName = FString();
		Value = FString();
	}

	FIniProperty(FString NewKeyName)
	{
		KeyName = NewKeyName;
		Value = FString();
	}

	FIniProperty(FString NewKeyName, FString NewValue)
	{
		KeyName = NewKeyName;
		Value = NewValue;
	}

public:
	FString ToString() const;

public:
	void operator=(const uint8_t& NewValue);
	void operator=(const int32& NewValue);
	void operator=(const int64& NewValue);
	void operator=(const FIntPoint& NewValue);
	void operator=(const bool& NewValue);
	void operator=(const double& NewValue);
	void operator=(const float& NewValue);
	void operator=(const FVector& NewValue);
	void operator=(const FVector3f& NewValue);
	void operator=(const FVector2D& NewValue);
	void operator=(const FIntVector& NewValue);
	void operator=(const FRotator& NewValue);
	void operator=(const FMatrix& NewValue);
	void operator=(const FName& NewValue);
	void operator=(const FString& NewValue);
	void operator=(const FText& NewValue);
	void operator=(UObject* NewValue);
	void operator=(const FTransform& NewValue);
	void operator=(const FLinearColor& NewValue);
	void operator=(const FInputDeviceId& NewValue);
	void operator=(const FPlatformUserId& NewValue);

	operator FString() const;
};