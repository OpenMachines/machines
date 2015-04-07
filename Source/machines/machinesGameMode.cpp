// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "machines.h"
#include "machinesGameMode.h"
//#include "machinesHUD.h"
//#include "machinesCharacter.h"

AmachinesGameMode::AmachinesGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/PlayerCamera"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	//HUDClass = AmachinesHUD::StaticClass();
}
