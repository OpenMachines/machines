// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "RTSCameraController.generated.h"

/**
 * 
 */
UCLASS()
class MACHINES_API ARTSCameraController : public APlayerController
{
	GENERATED_BODY()

		virtual void BeginPlay() override;
	
	
};
