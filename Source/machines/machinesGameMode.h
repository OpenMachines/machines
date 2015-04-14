// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "machinesGameMode.generated.h"

/* Used as an event that occurs once the selection box is hidden, and units should be selected. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSelectionAction);

/**
 * 
 */
UCLASS()
class MACHINES_API AmachinesGameMode : public AGameMode
{
	GENERATED_BODY()

	ADefaultPawn* CameraPawn;

	APlayerController* CameraController;

	TSubclassOf<APawn> PawnClass;

	TSubclassOf<APlayerController> ControllerClass;

	
public:

	FSelectionAction OnSelect;

	AmachinesGameMode(const FObjectInitializer& ObjectInitializer);
};
