﻿// Copyright 2021 Yevhenii Selivanov.

#pragma once

#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
//---
#include "Bomber.h"
//---
#include "SettingsRow.generated.h"

#define TEXT_NONE FCoreTexts::Get().None

/**	┌───────────────────────────┐
  *	│			[SETTINGS]		│ Header (title)
  *	│	[Option 1]	[Option 2]	│ Content (options)
  *	│			[GO BACK]		│ Footer
  *	└───────────────────────────┘ */
UENUM(BlueprintType)
enum class EMyVerticalAlignment : uint8
{
	Header,
	Content,
	Footer
};

/**
  * All UI states of the button.
  */
UENUM(BlueprintType)
enum class ESettingsButtonState : uint8
{
	Normal,
	Hovered,
	Pressed,
	Disabled
};

/**
  * All UI states of the checkbox.
  */
UENUM(BlueprintType)
enum class ESettingsCheckboxState : uint8
{
	UncheckedNormal,
	UncheckedHovered,
	UncheckedPressed,
	CheckedNormal,
	CheckedHovered,
	CheckedPressed,
	UndeterminedNormal,
	UndeterminedHovered,
	UndeterminedPressed
};

/**
  * All UI states of the slider.
  */
UENUM(BlueprintType)
enum class ESettingsSliderState : uint8
{
	NormalBar,
	HoveredBar,
	NormalThumb,
	HoveredThumb
};

/**
  * The parent struct of the settings theme data.
  */
USTRUCT(BlueprintType)
struct FSettingsThemeData
{
	GENERATED_BODY()

	/** The texture image of the setting. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	TObjectPtr<class UTexture> Texture = nullptr; //[B]

	/** The size of the resource in Slate Units. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FVector2D Size = FVector2D(64.f, 64.f); //[B]

	/** How to draw the image. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	TEnumAsByte<enum ESlateBrushDrawType::Type> DrawAs = ESlateBrushDrawType::Box; //[B]

	/** The margin to use in Box and Border modes. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FMargin Margin; //[B]

	/** Outside padding of the image. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FMargin Padding; //[B]
};

/**
  * The theme data of the settings button.
  */
USTRUCT(BlueprintType)
struct FButtonThemeData : public FSettingsThemeData
{
	GENERATED_BODY()

	/** The padding to used when button is pressed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FMargin PressedPadding; //[B]
};

/**
  * The theme data of the settings checkbox.
  * The parent Texture property determines of the unchecked checkbox.
  */
USTRUCT(BlueprintType)
struct FCheckboxThemeData : public FSettingsThemeData
{
	GENERATED_BODY()

	/** The texture image of the toggled checkbox. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	TObjectPtr<class UTexture> CheckedTexture = nullptr; //[B]

	/** The texture image of the undetermined checkbox. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	TObjectPtr<class UTexture> UndeterminedTexture = nullptr; //[B]
};

/**
  * The theme data of the settings combobox.
  */
USTRUCT(BlueprintType)
struct FComboboxThemeData : public FSettingsThemeData
{
	GENERATED_BODY()

	/** The padding to used when combobox is pressed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FMargin PressedPadding; //[B]

	/** The combobox arrow theme data. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSettingsThemeData Arrow; //[B]

	/** The combobox border theme data. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSettingsThemeData Border; //[B]

	/** The combobox background color */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateColor ItemBackgroundColor; //[B]
};

/**
  * The theme data of the settings slider.
  */
USTRUCT(BlueprintType)
struct FSliderThemeData : public FSettingsThemeData
{
	GENERATED_BODY()

	/** The theme of the slider thumb. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSettingsThemeData Thumb;
};

/**
  * The common theme data.
  */
USTRUCT(BlueprintType)
struct FMiscThemeData
{
	GENERATED_BODY()

	/** The common color of normal state for all setting types. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateColor ThemeColorNormal; //[B]

	/** The common color of hover state for all setting types. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateColor ThemeColorHover; //[B]

	/** The misc colors for all setting types. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateColor ThemeColorExtra; //[B]

	/** The font of text and captions. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateFontInfo TextAndCaptionFont; //[B]

	/** The color of text and captions. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateColor TextAndCaptionColor; //[B]

	/** The font of the header. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateFontInfo TextHeaderFont; //[B]

	/** The color of the header. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateColor TextHeaderColor; //[B]

	/** The font of the footer. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateFontInfo TextFooterFont; //[B]

	/** The color of the footer. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateColor TextFooterColor; //[B]

	/** The font of all setting values. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateFontInfo TextElementFont; //[B]

	/** The color of all setting values. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateColor TextElementColor; //[B]

	/** The theme data of tooltips. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSettingsThemeData TooltipBackground; //[B]

	/** The background color of tooltips. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateColor TooltipBackgroundTint; //[B]

	/** The theme data of the window background. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSettingsThemeData WindowBackground; //[B]

	/** The theme color of the window background. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateColor WindowBackgroundTint; //[B]

	/** The theme data of the menu border. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSettingsThemeData MenuBorderData; //[B]

	/** Color of the border. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	FSlateColor MenuBorderTint; //[B]

	/** Visibility of the border. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "C++")
	ESlateVisibility MenuBorderVisibility; //[B]
};

/* Structs dependencies:
 *
 * ╔FSettingsRow
 * ╚════╦FSettingsPicker
 *		╠═══╦FSettingsPrimary
 *		║	╚════FSettingsFunction
 *		╚════FSettingsDataBase
 */

/**
  * Delegates wrapper that are used as templates for FSettingsFunction properties.
  * Has to have reflection to allow find its members by FSettingsFunctionCustomization:
  * USettingTemplate::StaticClass()->FindFunctionByName("OnStaticContext__DelegateSignature");
  * DECLARE_DYNAMIC_DELEGATE can't be declared under USTRUCT
  */
UCLASS(Abstract, Const, Transient)
class BOMBER_API USettingTemplate final : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_DELEGATE_RetVal(UObject*, FOnStaticContext);

	DECLARE_DYNAMIC_DELEGATE(FOnButtonPressed);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetterInt, int32, Param);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetterFloat, float, Param);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetterBool, bool, Param);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetterText, FText, Param);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetMembers, const TArray<FText>&, NewMembers);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetterName, FName, Param);

	DECLARE_DYNAMIC_DELEGATE_RetVal(int32, FOnGetterInt);

	DECLARE_DYNAMIC_DELEGATE_RetVal(float, FOnGetterFloat);

	DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FOnGetterBool);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetterText, FText&, OutParam);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetMembers, TArray<FText>&, OutParam);

	DECLARE_DYNAMIC_DELEGATE_RetVal(FName, FOnGetterName);
};

/**
  * Function wrapper.
  */
USTRUCT(BlueprintType)
struct FSettingsFunction
{
	GENERATED_BODY()

	/** Empty settings function. */
	static const FSettingsFunction Empty;

	/** Default constructor. */
	FSettingsFunction() = default;

	/** Custom constructor to set all members values. */
	FSettingsFunction(TSubclassOf<UObject> InFunctionClass, FName InFunctionName);

	/** The class where function can be found. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++", meta = (DisplayName = "Class"))
	TSubclassOf<UObject> FunctionClass = nullptr; //[D]

	/** The function name to choose for specified class.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++", meta = (DisplayName = "Function"))
	FName FunctionName = NAME_None; //[D]

	/** Returns true if is valid. */
	FORCEINLINE bool IsValid() const { return !(*this == Empty); }

	/** Compares for equality.
	  * @param Other The other object being compared. */
	bool operator==(const FSettingsFunction& Other) const;

	/** Creates a hash value.
	  * @param Other the other object to create a hash value for. */
	friend uint32 GetTypeHash(const FSettingsFunction& Other);
};

/**
  * The primary data of any setting.
  * Does not contain a default states for its value, because it should be set in the DefaultGameUserSettings.ini
  */
USTRUCT(BlueprintType)
struct FSettingsPrimary
{
	GENERATED_BODY()

	/** The tag of the setting. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	FGameplayTag Tag = FGameplayTag::EmptyTag; //[D]

	/** The static function to obtain object to call Setters and Getters.
	  * The SettingsFunctionContextTemplate meta will contain a name of one USettingTemplate delegate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++", meta = (SettingsFunctionContextTemplate))
	FSettingsFunction StaticContext = FSettingsFunction::Empty; //[D]

	/** The Setter function to be called to set the setting value for the Static Context object.
	  * The SettingsFunctionSetterTemplate meta will contain a name of one USettingTemplate delegate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++", meta = (SettingsFunctionSetterTemplate))
	FSettingsFunction Setter = FSettingsFunction::Empty; //[D]

	/** The Getter function to be called to get the setting value from the Static Context object.
	  * The SettingsFunctionGetterTemplate meta will contain a name of one USettingTemplate delegate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++", meta = (SettingsFunctionGetterTemplate))
	FSettingsFunction Getter = FSettingsFunction::Empty; //[D]

	/** The setting name. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	FText Caption = TEXT_NONE; //[D]

	/** The description to be shown as tooltip. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	FText Tooltip = TEXT_NONE; //[D]

	/** The padding of this setting. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	FMargin Padding = 0.f; //[D]

	/** Set true to add new column starting from this setting. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	bool bStartOnNextColumn; //[D]

	/** The cached object obtained from the Static Context function. */
	TWeakObjectPtr<UObject> StaticContextObject;

	/** Contains all cached functions of the Static Context object. */
	TArray<FName> StaticContextFunctionList;

	/** Returns true if is valid. */
	FORCEINLINE bool IsValid() const { return Tag.IsValid(); }

	/** Compares for equality.
	* @param Other The other object being compared. */
	bool operator==(const FSettingsPrimary& Other) const;

	/** Creates a hash value.
	* @param Other the other object to create a hash value for. */
	friend uint32 GetTypeHash(const FSettingsPrimary& Other);
};

/**
  * The base archetype of some setting.
  */
USTRUCT(BlueprintType, meta = (
	SettingsFunctionContextTemplate="OnStaticContext__DelegateSignature"))
struct FSettingsDataBase
{
	GENERATED_BODY()
};

/**
  * The setting button data.
  */
USTRUCT(BlueprintType, meta = (
	SettingsFunctionSetterTemplate="OnButtonPressed__DelegateSignature"))
struct FSettingsButton : public FSettingsDataBase
{
	GENERATED_BODY()

	/** Either Header, Content, or Footer. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	EMyVerticalAlignment VerticalAlignment = EMyVerticalAlignment::Content; //[D]

	/** Either Left, Right, Center, or Fill. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = HAlign_Fill; //[D]

	/** Set custom line height for this setting, 0 to use current line height. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	float LineHeight = 0.f; //[D]

	/** Cached bound delegate, is executed on pressing this button. */
	USettingTemplate::FOnButtonPressed OnButtonPressed;
};

/**
  * The setting checkbox data.
  */
USTRUCT(BlueprintType, meta = (
	SettingsFunctionSetterTemplate="OnSetterBool__DelegateSignature",
	SettingsFunctionGetterTemplate="OnGetterBool__DelegateSignature"))
struct FSettingsCheckbox : public FSettingsDataBase
{
	GENERATED_BODY()

	/** The cached current checkbox state. */
	bool bIsSet = false;

	/** The cached bound delegate, is executed to get the current checkbox state. */
	USettingTemplate::FOnGetterBool OnGetterBool;

	/** The cached bound delegate, is executed to set the current checkbox state. */
	USettingTemplate::FOnSetterBool OnSetterBool;
};

/**
  * The setting combobox data.
  */
USTRUCT(BlueprintType, meta = (
	SettingsFunctionSetterTemplate="OnSetterInt__DelegateSignature",
	SettingsFunctionGetterTemplate="OnGetterInt__DelegateSignature"))
struct FSettingsCombobox : public FSettingsDataBase
{
	GENERATED_BODY()

	/** The Setter function to be called to set all combobox members. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++", meta = (SettingsFunctionSetterTemplate="OnSetMembers__DelegateSignature"))
	FSettingsFunction SetMembers = FSettingsFunction::Empty; //[D]

	/** The Setter function to be called to get all combobox members. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++", meta = (SettingsFunctionGetterTemplate="OnGetMembers__DelegateSignature"))
	FSettingsFunction GetMembers = FSettingsFunction::Empty; //[D]

	/** Contains all combobox members. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	TArray<FText> Members; //[D]

	/** Text alignment either left, center, or right. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	TEnumAsByte<ETextJustify::Type> TextJustify = ETextJustify::Center; //[D]

	/** The cached chosen member index. */
	int32 ChosenMemberIndex = INDEX_NONE;

	/** The cached bound delegate, is executed to get the chosen member index. */
	USettingTemplate::FOnGetterInt OnGetterInt;

	/** The cached bound delegate, is executed to set the chosen member index. */
	USettingTemplate::FOnSetterInt OnSetterInt;

	/** The cached bound delegate, is executed to get all combobox members. */
	USettingTemplate::FOnGetMembers OnGetMembers;

	/** The cached bound delegate, is executed to set all combobox members. */
	USettingTemplate::FOnSetMembers OnSetMembers;
};

/**
  * The setting slider data.
  */
USTRUCT(BlueprintType, meta = (
	SettingsFunctionSetterTemplate="OnSetterFloat__DelegateSignature",
	SettingsFunctionGetterTemplate="OnGetterFloat__DelegateSignature"))
struct FSettingsSlider : public FSettingsDataBase
{
	GENERATED_BODY()

	/** Cached slider value (0..1). */
	float ChosenValue = 0.f;

	/** The cached bound delegate, is executed to get the current slider value. */
	USettingTemplate::FOnGetterFloat OnGetterFloat;

	/** The cached bound delegate, is executed to set the current slider value. */
	USettingTemplate::FOnSetterFloat OnSetterFloat;
};

/**
  * The setting text line data.
  */
USTRUCT(BlueprintType, meta = (
	SettingsFunctionSetterTemplate="OnSetterText__DelegateSignature",
	SettingsFunctionGetterTemplate="OnGetterText__DelegateSignature"))
struct FSettingsTextLine : public FSettingsDataBase
{
	GENERATED_BODY()

	/** Either Header, Content, or Footer. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	EMyVerticalAlignment VerticalAlignment = EMyVerticalAlignment::Content; //[D]

	/** Either Left, Right, Center, or Fill. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = HAlign_Fill; //[D]

	/** The cached bound delegate, is executed to set the text caption. */
	USettingTemplate::FOnGetterText OnGetterText;

	/** The cached bound delegate, is executed to get the text caption. */
	USettingTemplate::FOnSetterText OnSetterText;
};

/**
  * The setting user input data.
  */
USTRUCT(BlueprintType, meta = (
	SettingsFunctionSetterTemplate="OnSetterName__DelegateSignature",
	SettingsFunctionGetterTemplate="OnGetterName__DelegateSignature"))
struct FSettingsUserInput : public FSettingsDataBase
{
	GENERATED_BODY()

	/** The cached text shown left of the input box. */
	FName UserInput = NAME_None;

	/** The cached bound delegate, is executed to set the input text. */
	USettingTemplate::FOnGetterName OnGetterName;

	/** The cached bound delegate, is executed to get the input text. */
	USettingTemplate::FOnSetterName OnSetterName;
};

/**
  * Is customizable struct, its members were created under FSettingsPicker ...
  * (instead of FSettingsRow which implements table row struct and can't be customized),
  * to have possibility to be property-customized by FSettingsPickerCustomization,
  * which allows to show only selected in-game option.
  */
USTRUCT(BlueprintType)
struct FSettingsPicker
{
	GENERATED_BODY()

	/** Nothing picked. */
	static const FSettingsPicker Empty;

	/** Contains a in-game settings type to be used - the name of one of these members. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	FName SettingsType = NAME_None; //[D]

	/** The common setting data. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	FSettingsPrimary PrimaryData;

	/** The button setting data. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	FSettingsButton Button; //[D]

	/** The checkbox setting data. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	FSettingsCheckbox Checkbox; //[D]

	/** The combobox setting data. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	FSettingsCombobox Combobox; //[D]

	/** The slider setting data. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	FSettingsSlider Slider; //[D]

	/** The text line setting data. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	FSettingsTextLine TextLine; //[D]

	/** The user input setting data. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	FSettingsUserInput UserInput; //[D]

	/** Returns the pointer to one of the chosen in-game type.
	  * It searches the member property of this struct by a value of SettingsType.
	  * @see FSettingsPicker::SettingsType */
	const FSettingsDataBase* GetChosenSettingsData() const;

	/** Returns true if row is valid. */
	FORCEINLINE bool IsValid() const { return !(*this == Empty); }

	/** Compares for equality.
	  * @param Other The other object being compared. */
	bool operator==(const FSettingsPicker& Other) const;

	/** Creates a hash value.
	  * @param Other the other object to create a hash value for. */
	friend uint32 GetTypeHash(const FSettingsPicker& Other);
};

/**
  * Row of the settings data table.
  * In a row can be specified all UI values, chosen any getter/setter in the list.
  * Main features:
  * By this row, new setting will be automatically added on UI.
  * Executing UI getters/setters will call automatically bounded chosen functions.
  */
USTRUCT(BlueprintType)
struct FSettingsRow : public FTableRowBase
{
	GENERATED_BODY()

	/** The setting row to be customised. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++")
	FSettingsPicker SettingsPicker = FSettingsPicker::Empty; //[D]
};
