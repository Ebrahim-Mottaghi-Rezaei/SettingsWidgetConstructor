﻿// Copyright (c) Yevhenii Selivanov.

#include "MySettingsEditor.h"

#define LOCTEXT_NAMESPACE "FMySettingsEditorModule"

// Called right after the module DLL has been loaded and the module object has been created
void FMySettingsEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

// Called before the module is unloaded, right before the module object is destroyed
void FMySettingsEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMySettingsEditorModule, MySettingsEditor)
