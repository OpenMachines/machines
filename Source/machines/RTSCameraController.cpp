// Fill out your copyright notice in the Description page of Project Settings.

#include "machines.h"
#include "RTSCameraController.h"

void ARTSCameraController::BeginPlay()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;	
}