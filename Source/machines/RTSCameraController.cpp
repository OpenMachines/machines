// Fill out your copyright notice in the Description page of Project Settings.

#include "machines.h"
#include "RTSCameraController.h"
#include "RTSHUD.h"
#include "machinesGameMode.h"

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
			//UE_LOG(LogTemp, Warning, TEXT("One command sent!"));
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



		//UE_LOG(LogTemp, Warning, TEXT("Cursor Delta Movement: %f"), cursorDelta);

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
			UE_LOG(LogTemp, Warning, TEXT("Found Actor"));

			ARTSUnit* unit = Cast<ARTSUnit>(Hit.GetActor());
		
			if (unit != NULL)
			{
				UE_LOG(LogTemp, Warning, TEXT("Selected unit with click!"));
				unit->SelectExclusive();
				return true;
			}
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Did not select a unit. Deselecting."));
	return false;
}

/* Selects a specified unit. */
void ARTSCameraController::SelectUnit(ARTSUnit* Unit)
{
	Unit->bIsSelected = true;
	SelectedUnits.Add(Unit);
	UE_LOG(LogTemp, Warning, TEXT("Yes?"));
}

/* Deselects all selected units. */
void ARTSCameraController::DeselectUnits()
{
	for (ARTSUnit* Unit : SelectedUnits){
		Unit->bIsSelected = false;
	}
	SelectedUnits.Empty();
}