// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "RTSUnit.h"
#include "RTSCameraController.generated.h"

/**
 * Used to control base player pawn, ARTSCamera.
 * Control functions are all defined in that class.
 */
UCLASS()
class MACHINES_API ARTSCameraController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	
public:

	// The player's HUD object.
	class ARTSHUD* HUD;

	/* Checks if the player is attempting to select units. */
	void CheckForSelection();

	/* Checks if the player is attempting to select units. */
	bool CheckForClickSelection();

	/* Checks for a player sent command every frame. */
	virtual void Tick(float DeltaSeconds) override;

	/* Array of all selected units. */
	static TArray<ARTSUnit*> SelectedUnits;

	/* Select a specified unit. */
	static void SelectUnit(ARTSUnit* Unit);

	/* Deselect all selected units. */
	static void DeselectUnits();

private:

	/* Start position of selection box. */
	FVector2D StartPos;

};
