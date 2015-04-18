// Fill out your copyright notice in the Description page of Project Settings.

#include "machines.h"
#include "RTSCameraController.h"

TArray<ARTSUnit*> ARTSCameraController::SelectedUnits;

/* Called when the game starts or when spawned. Enables cursor controls. */
void ARTSCameraController::BeginPlay()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;	
}

/* Selects a specified unit. */
void ARTSCameraController::SelectUnit(ARTSUnit* Unit)
{
	Unit->bIsSelected = true;
	SelectedUnits.Add(Unit);
}

/* Deselects all selected units. */
void ARTSCameraController::DeselectUnits()
{
	for (ARTSUnit* Unit : SelectedUnits){
		Unit->bIsSelected = false;
	}
	SelectedUnits.Empty();
}