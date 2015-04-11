// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "machinesGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MACHINES_API AmachinesGameMode : public AGameMode
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	ADefaultPawn* CameraPawn;
	APlayerController* CameraController;
	TSubclassOf<APawn> PawnClass;
	TSubclassOf<APlayerController> ControllerClass;
public:
	AmachinesGameMode(const FObjectInitializer& ObjectInitializer);
};
