// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "machines.h"
#include "machinesGameMode.h"
#include "RTSCamera.h"

/* Sets default class values. */
AmachinesGameMode::AmachinesGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set default pawn class to the ARTSCamera class.
	static ConstructorHelpers::FClassFinder<ADefaultPawn> PlayerPawnClassFinder(TEXT("Class'/Script/machines.RTSCamera'"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	
	// Set default player controller class to the ARTSCameraController class.
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("Class'/Script/machines.RTSCameraController'"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;

	// Set default HUD class to the ARTSHUD class.
	static ConstructorHelpers::FClassFinder<AHUD> HUDClassFinder(TEXT("Class'/Script/machines.RTSHUD'"));	
	HUDClass = HUDClassFinder.Class;
}