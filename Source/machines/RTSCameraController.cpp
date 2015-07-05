// Fill out your copyright notice in the Description page of Project Settings.

#include "machines.h"
#include "RTSCameraController.h"
#include "RTSHUD.h"
#include "machinesGameMode.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

TArray<ARTSUnit*> ARTSCameraController::SelectedUnits;

/* Called when the game starts or when spawned. Enables cursor controls. */
void ARTSCameraController::BeginPlay()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;	
	PrimaryActorTick.bCanEverTick = true;

	// Assign hud reference.
	HUD = (ARTSHUD*) GetHUD();
}

/* Checks for a player sent command every frame. */
void ARTSCameraController::Tick(float DeltaTime)
{
	if (WasInputKeyJustReleased(EKeys::RightMouseButton))
	{		
		for (ARTSUnit* Unit : SelectedUnits)
		{
			Unit->PerformCommand();
		}
	}

	CheckForSelection();
}

/* Checks if the player is attempting to select units. */
void ARTSCameraController::CheckForSelection()
{
	/* If left mouse was pressed. */
	if (WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		GetMousePosition(StartPos.X, StartPos.Y);

		/* Show the selection box. */
		HUD->ShowSelectionBox();
	}

	/* If left mouse was released. */
	if (WasInputKeyJustReleased(EKeys::LeftMouseButton))
	{

		//Store mouse position when mouse is released
		FVector2D NewMousePos;
		GetMousePosition(NewMousePos.X, NewMousePos.Y);

		float cursorDelta = FVector2D::Distance(StartPos, NewMousePos);

		//If we dragged a selection box instead of just clicked
		if (cursorDelta>5.0f)
		{
			// Always deselect before selecting units!
			DeselectUnits();

			// Let units check if they are within the selection box.
			AmachinesGameMode* GameMode = (AmachinesGameMode*)GetWorld()->GetAuthGameMode();
			GameMode->OnSelect.Broadcast();
		}
		// If it was just a click:
		else
		{
			if (!CheckForClickSelection())
			{
				DeselectUnits();
			}
		}

		/* Hide the selection box. */
		HUD->HideSelectionBox();
	}
}

/* Checks if the player is attempting to select with a click. */
bool ARTSCameraController::CheckForClickSelection()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Pawn, false, Hit);

	if (Hit.bBlockingHit)
	{

		if (Hit.Actor != NULL)
		{
			print(Hit.GetActor()->GetName());

			ARTSUnit* unit = Cast<ARTSUnit>(Hit.GetActor());
		
			if (unit != NULL)
			{
				unit->SelectExclusive();
				return true;
			}
		}
	}
	return false;
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