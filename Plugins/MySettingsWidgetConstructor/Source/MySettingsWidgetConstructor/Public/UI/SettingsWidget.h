﻿// Copyright (c) Yevhenii Selivanov

#pragma once

#include "Blueprint/UserWidget.h"
//---
#include "Structures/SettingsRow.h"
//---
#include "SettingsWidget.generated.h"

/**
 * The UI widget of settings.
 * It generates and manages settings specified in rows of the Settings Data Table.
 */
UCLASS()
class MYSETTINGSWIDGETCONSTRUCTOR_API USettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/* ---------------------------------------------------
	 *		Public properties
	 * --------------------------------------------------- */

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToggledSettings, bool, bIsVisible);

	/** Is called to notify listeners the Settings widget is opened or closed. */
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "C++")
	FOnToggledSettings OnToggledSettings;

	/* ---------------------------------------------------
	 *		Public functions
	 * --------------------------------------------------- */

	/** Returns the settings data.*/
	UFUNCTION(BlueprintPure, Category = "C++")
	const FORCEINLINE class USettingsDataAsset* GetSettingsDataAsset() const { return SettingsDataAssetInternal; }

	/** Display settings on UI. */
	UFUNCTION(BlueprintCallable, Category = "C++")
	void OpenSettings();

	/** Is called on displayed settings on UI. */
	UFUNCTION(BlueprintImplementableEvent, Category = "C++")
	void OnOpenSettings();

	/** Save and close the settings widget. */
	UFUNCTION(BlueprintCallable, Category = "C++")
	void CloseSettings();

	/** Is called on closed settings on UI. */
	UFUNCTION(BlueprintImplementableEvent, Category = "C++")
	void OnCloseSettings();

	/** Flip-flop opens and closes the Settings menu. */
	UFUNCTION(BlueprintCallable, Category = "C++")
	void ToggleSettings();

	/** Is called to player sound effect on any setting click. */
	UFUNCTION(BlueprintImplementableEvent, Category = "C++")
	void PlayUIClickSFX();

	/** Returns the amount of settings rows. */
	UFUNCTION(BlueprintPure, Category = "C++")
	FORCEINLINE int32 GetSettingsTableRowsNum() const { return SettingsTableRowsInternal.Num(); }

	/** Try to find the setting row.
	* @param PotentialTagName The probable tag name by which the row will be found (for 'VSync' will find a row with 'Settings.Checkbox.VSync' tag).
	* @see UMyGameUserSettings::SettingsTableRowsInternal */
	UFUNCTION(BlueprintPure, Category = "C++")
	const FSettingsPicker& FindSettingRow(FName PotentialTagName) const;

	/** Returns the found row by specified tag.
	* @param SettingTag The gameplay tag by which the row will be found. */
	UFUNCTION(BlueprintPure, Category = "C++", meta = (AutoCreateRefTerm = "SettingTag"))
	const FSettingsPicker& GetSettingRow(const FSettingTag& SettingTag) const;

	/** Save all settings into their configs. */
	UFUNCTION(BlueprintCallable, Category = "C++")
	void SaveSettings();

	/** Apply all current settings on device. */
	UFUNCTION(BlueprintCallable, Category = "C++")
	void ApplySettings();

	/** Update settings on UI.
	 * @param SettingsToUpdate Contains tags of settings that are needed to update. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (AutoCreateRefTerm = "SettingsToUpdate"))
	void UpdateSettings(
		UPARAM(meta = (Categories = "Settings")) const FGameplayTagContainer& SettingsToUpdate);

	/** Returns the name of found tag by specified function. */
	UFUNCTION(BlueprintPure, Category = "C++", meta = (AutoCreateRefTerm = "FunctionPicker"))
	const FSettingTag& GetTagByFunctionPicker(const FFunctionPicker& FunctionPicker) const;

	/* ---------------------------------------------------
	 *		Setters by setting types
	 * --------------------------------------------------- */

	/**
   	  * Set value to the option by tag.
   	  * Common function to set setting of an any type by the string.
   	  * Used by cheat manager to override any setting.
	  *	@param TagName The key by which the row will be find.
	  * @param Value The value in a string format.
	  */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (AutoCreateRefTerm = "Value"))
	void SetSettingValue(FName TagName, const FString& Value);

	/** Press button. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (AutoCreateRefTerm = "ButtonTag"))
	void SetSettingButtonPressed(const FSettingTag& ButtonTag);

	/** Toggle checkbox. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (AutoCreateRefTerm = "CheckboxTag"))
	void SetSettingCheckbox(const FSettingTag& CheckboxTag, bool InValue);

	/** Set chosen member index for a combobox. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (AutoCreateRefTerm = "ComboboxTag"))
	void SetSettingComboboxIndex(const FSettingTag& ComboboxTag, int32 InValue);

	/** Set new members for a combobox. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (AutoCreateRefTerm = "ComboboxTag,InValue"))
	void SetSettingComboboxMembers(const FSettingTag& ComboboxTag, const TArray<FText>& InValue);

	/** Set current value for a slider [0...1]. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (AutoCreateRefTerm = "SliderTag"))
	void SetSettingSlider(const FSettingTag& SliderTag, float InValue);

	/** Set new text. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (AutoCreateRefTerm = "TextLineTag,InValue"))
	void SetSettingTextLine(const FSettingTag& TextLineTag, const FText& InValue);

	/** Set new text for an input box. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (AutoCreateRefTerm = "UserInputTag"))
	void SetSettingUserInput(const FSettingTag& UserInputTag, FName InValue);

	/** Set new custom widget for setting by specified tag. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (AutoCreateRefTerm = "CustomWidgetTag"))
	void SetSettingCustomWidget(const FSettingTag& CustomWidgetTag, class USettingCustomWidget* InCustomWidget);

	/* ---------------------------------------------------
	 *		Getters by setting types
	 * --------------------------------------------------- */

	/** Returns is a checkbox toggled. */
	UFUNCTION(BlueprintPure, Category = "C++", meta = (AutoCreateRefTerm = "CheckboxTag"))
	bool GetCheckboxValue(const FSettingTag& CheckboxTag) const;

	/** Returns chosen member index of a combobox. */
	UFUNCTION(BlueprintPure, Category = "C++", meta = (AutoCreateRefTerm = "ComboboxTag"))
	int32 GetComboboxIndex(const FSettingTag& ComboboxTag) const;

	/** Get all members of a combobox. */
	UFUNCTION(BlueprintPure, Category = "C++", meta = (AutoCreateRefTerm = "ComboboxTag"))
	void GetComboboxMembers(const FSettingTag& ComboboxTag, TArray<FText>& OutMembers) const;

	/** Get current value of a slider [0...1]. */
	UFUNCTION(BlueprintPure, Category = "C++", meta = (AutoCreateRefTerm = "SliderTag"))
	float GetSliderValue(const FSettingTag& SliderTag) const;

	/** Get current text of the text line setting. */
	UFUNCTION(BlueprintPure, Category = "C++", meta = (AutoCreateRefTerm = "TextLineTag"))
	void GetTextLineValue(const FSettingTag& TextLineTag, FText& OutText) const;

	/** Get current input name of the text input setting. */
	UFUNCTION(BlueprintPure, Category = "C++", meta = (AutoCreateRefTerm = "UserInputTag"))
	FName GetUserInputValue(const FSettingTag& UserInputTag) const;

	/** Get custom widget of the setting by specified tag.  */
	UFUNCTION(BlueprintPure, Category = "C++", meta = (AutoCreateRefTerm = "CustomWidgetTag"))
	class USettingCustomWidget* GetCustomWidget(const FSettingTag& CustomWidgetTag) const;

	/** Get setting widget object by specified tag. */
	UFUNCTION(BlueprintPure, Category = "C++", meta = (AutoCreateRefTerm = "SettingTag"))
	class USettingSubWidget* GetSettingSubWidget(const FSettingTag& SettingTag) const;

protected:
	/* ---------------------------------------------------
	 *		Protected properties
	 * --------------------------------------------------- */

	/** Settings data. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++", meta = (BlueprintProtected, DisplayName = "Settings Data Asset", ShowOnlyInnerProperties))
	TObjectPtr<class USettingsDataAsset> SettingsDataAssetInternal = nullptr; //[B]

	/** Contains all settings. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Transient, Category = "C++", meta = (BlueprintProtected, DisplayName = "Settings Table Rows"))
	TMap<FName/*Tag*/, FSettingsPicker/*Row*/> SettingsTableRowsInternal; //[G]

	/** The index of the current column. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Transient, Category = "C++", meta = (BlueprintProtected, DisplayName = "Current Column Index"))
	int32 CurrentColumnIndexInternal = 0; //[G]

	/** Is set automatically on started by amount of rows that are marked to be started on next column. Settings have at least one column. */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Transient, Category = "C++", meta = (BlueprintProtected, DisplayName = "Overall Columns Num"))
	int32 OverallColumnsNumInternal = 1; //[G]

	/* ---------------------------------------------------
	*		Protected functions
	* --------------------------------------------------- */

	/** Called after the underlying slate widget is constructed.
	* May be called multiple times due to adding and removing from the hierarchy. */
	virtual void NativeConstruct() override;

	/** Construct all settings from the settings data table. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++", meta = (BlueprintProtected))
	void ConstructSettings();

	/** Is called when In-Game menu became opened or closed. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (BlueprintProtected))
	void OnToggleSettings(bool bIsVisible);

	/** Bind and set static object delegate.
	* @see FSettingsPrimary::OnStaticContext */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (BlueprintProtected))
	void TryBindStaticContext(UPARAM(ref)FSettingsPrimary& Primary);

	/** Creates setting sub-widget (like button, checkbox etc.) based on specified setting class and sets it to specified primary data.
	* @param Primary The Data that should contain created setting class.
	* @param SettingSubWidgetClass The setting widget class to create. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (BlueprintProtected, AutoCreateRefTerm = "Primary,SettingSubWidgetClass"))
	void CreateSettingSubWidget(FSettingsPrimary& Primary, const TSubclassOf<USettingSubWidget>& SettingSubWidgetClass);

	/** Starts adding settings on the next column. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++", meta = (BlueprintProtected))
	void StartNextColumn();

	/* ---------------------------------------------------
	 *		Add by setting types
	 * --------------------------------------------------- */

	/** Add setting on UI. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (BlueprintProtected))
	void AddSetting(UPARAM(ref)FSettingsPicker& Setting);

	/** Add button on UI. */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "C++", meta = (BlueprintProtected, AutoCreateRefTerm = "Primary,Data"))
	void AddButton(const FSettingsPrimary& Primary, const FSettingsButton& Data);
	void AddSettingButton(FSettingsPrimary& Primary, FSettingsButton& Data);

	/** Add checkbox on UI. */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "C++", meta = (BlueprintProtected, AutoCreateRefTerm = "Primary,Data"))
	void AddCheckbox(const FSettingsPrimary& Primary, const FSettingsCheckbox& Data);
	void AddSettingCheckbox(FSettingsPrimary& Primary, FSettingsCheckbox& Data);

	/** Add combobox on UI. */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "C++", meta = (BlueprintProtected, AutoCreateRefTerm = "Primary,Data"))
	void AddCombobox(const FSettingsPrimary& Primary, const FSettingsCombobox& Data);
	void AddSettingCombobox(FSettingsPrimary& Primary, FSettingsCombobox& Data);

	/** Add slider on UI. */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "C++", meta = (BlueprintProtected, AutoCreateRefTerm = "Primary,Data"))
	void AddSlider(const FSettingsPrimary& Primary, const FSettingsSlider& Data);
	void AddSettingSlider(FSettingsPrimary& Primary, FSettingsSlider& Data);

	/** Add simple text on UI. */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "C++", meta = (BlueprintProtected, AutoCreateRefTerm = "Primary,Data"))
	void AddTextLine(const FSettingsPrimary& Primary, const FSettingsTextLine& Data);
	void AddSettingTextLine(FSettingsPrimary& Primary, FSettingsTextLine& Data);

	/** Add text input on UI. */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "C++", meta = (BlueprintProtected, AutoCreateRefTerm = "Primary,Data"))
	void AddUserInput(const FSettingsPrimary& Primary, const FSettingsUserInput& Data);
	void AddSettingUserInput(FSettingsPrimary& Primary, FSettingsUserInput& Data);

	/** Add custom widget on UI.  */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "C++", meta = (BlueprintProtected, AutoCreateRefTerm = "Primary,Data"))
	void AddCustomWidget(const FSettingsPrimary& Primary, const FSettingsCustomWidget& Data);
	void AddSettingCustomWidget(FSettingsPrimary& Primary, FSettingsCustomWidget& Data);

	/* ---------------------------------------------------
	 *		Blueprint implementable setters
	 * --------------------------------------------------- */

	/** Internal blueprint function to toggle checkbox. */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "C++", meta = (BlueprintProtected, AutoCreateRefTerm = "CheckboxTag"))
	void SetCheckbox(const FSettingTag& CheckboxTag, bool InValue);

	/** Internal blueprint function to set chosen member index for a combobox. */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "C++", meta = (BlueprintProtected, AutoCreateRefTerm = "ComboboxTag"))
	void SetComboboxIndex(const FSettingTag& ComboboxTag, int32 InValue);

	/** Internal blueprint function to set new members for a combobox. */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "C++", meta = (BlueprintProtected, AutoCreateRefTerm = "ComboboxTag,InValue"))
	void SetComboboxMembers(const FSettingTag& ComboboxTag, const TArray<FText>& InValue);

	/** Internal blueprint function to set current value for a slider [0...1]. */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "C++", meta = (BlueprintProtected, AutoCreateRefTerm = "SliderTag"))
	void SetSlider(const FSettingTag& SliderTag, float InValue);

	/** Internal blueprint function to set new text for an input box. */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "C++", meta = (BlueprintProtected, AutoCreateRefTerm = "UserInputTag"))
	void SetUserInput(const FSettingTag& UserInputTag, FName InValue);
};
