// Copyright 2021 Yevhenii Selivanov.

#include "Structures/SettingsRow.h"

// Empty settings function
const FSettingsFunction FSettingsFunction::Empty = FSettingsFunction();

// Empty settings row
const FSettingsPicker FSettingsPicker::Empty = FSettingsPicker();

//
bool FSettingsFunction::operator==(const FSettingsFunction& Other) const
{
	return GetTypeHash(*this) == GetTypeHash(Other);
}

//
uint32 GetTypeHash(const FSettingsFunction& Other)
{
	const uint32 FunctionClassHash = GetTypeHash(Other.FunctionClass);
	const uint32 FunctionNameHash = GetTypeHash(Other.FunctionName);
	return HashCombine(FunctionClassHash, FunctionNameHash);
}

//
bool FSettingsPrimary::operator==(const FSettingsPrimary& Other) const
{
	return GetTypeHash(*this) == GetTypeHash(Other);
}

//
uint32 GetTypeHash(const FSettingsPrimary& Other)
{
	const uint32 TagHash = GetTypeHash(Other.Tag);
	const uint32 ObjectContextHash = GetTypeHash(Other.StaticContext);
	const uint32 SetterHash = GetTypeHash(Other.Setter);
	const uint32 GetterHash = GetTypeHash(Other.Getter);
	const uint32 CaptionHash = GetTypeHash(Other.Caption.ToString());
	const uint32 TooltipHash = GetTypeHash(Other.Tooltip.ToString());
	const uint32 PaddingLeftHash = GetTypeHash(Other.PaddingLeft);
	const uint32 PaddingTopHash = GetTypeHash(Other.PaddingTop);
	const uint32 PaddingRightHash = GetTypeHash(Other.PaddingRight);
	const uint32 PaddingBottomHash = GetTypeHash(Other.PaddingBottom);
	return HashCombine(HashCombine(HashCombine(HashCombine(HashCombine(HashCombine(HashCombine(HashCombine(HashCombine(
		TagHash, ObjectContextHash), SetterHash), GetterHash), CaptionHash), TooltipHash), PaddingLeftHash), PaddingTopHash), PaddingRightHash), PaddingBottomHash);
}

//
const FSettingsDataBase* FSettingsPicker::GetChosenSettingsData() const
{
	const FSettingsDataBase* FoundSetting = nullptr;
	if (!SettingsType.IsNone())
	{
		static const UScriptStruct* const& SettingsPickerStruct = StaticStruct();
		const FProperty* FoundProperty = SettingsPickerStruct ? SettingsPickerStruct->FindPropertyByName(SettingsType) : nullptr;
		const FStructProperty* FoundStructProperty = CastField<FStructProperty>(FoundProperty);
		FoundSetting = FoundStructProperty ? FoundStructProperty->ContainerPtrToValuePtr<FSettingsDataBase>(this, 0) : nullptr;
	}
	return FoundSetting;
}

//
bool FSettingsPicker::operator==(const FSettingsPicker& Other) const
{
	return GetChosenSettingsData() == Other.GetChosenSettingsData()
	       && GetTypeHash(*this) == GetTypeHash(Other);
}

//
uint32 GetTypeHash(const FSettingsPicker& Other)
{
	return GetTypeHash(Other.PrimaryData);
}
