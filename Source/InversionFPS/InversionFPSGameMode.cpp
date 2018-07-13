// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "InversionFPSGameMode.h"
#include "InversionFPSHUD.h"
#include "InversionFPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInversionFPSGameMode::AInversionFPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AInversionFPSHUD::StaticClass();
}
