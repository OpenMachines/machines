// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "machines.h"
#include "machinesGameMode.h"
#include "RTSCamera.h"

AmachinesGameMode::AmachinesGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<ADefaultPawn> PlayerPawnClassFinder(TEXT("Class'/Script/machines.RTSCamera'"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("Class'/Script/machines.RTSCameraController'"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;
}

void AmachinesGameMode::BeginPlay()
{
	PlayerControllerClass->GetDefaultObject<APlayerController>()->bShowMouseCursor;
}