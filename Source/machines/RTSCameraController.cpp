// Fill out your copyright notice in the Description page of Project Settings.

#include "machines.h"
#include "RTSCameraController.h"

/* Called when the game starts or when spawned. Enables cursor controls. */
void ARTSCameraController::BeginPlay()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;	
}