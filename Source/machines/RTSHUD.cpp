// Fill out your copyright notice in the Description page of Project Settings.

#include "machines.h"
#include "RTSHUD.h"
#include "machinesGameMode.h"
#include "RTSCameraController.h"

//Initialize static members.
Rect* ARTSHUD::SelectionBox = new Rect(0, 0, 0, 0);

/* Called when the game starts or when spawned. */
void ARTSHUD::BeginPlay()
{
	PC = GetWorld()->GetFirstPlayerController();
}

/* Called every frame. */
void ARTSHUD::Tick(float Deltatime)
{
	CheckForInput();
}

/* Checks to see if left mouse was pressed or released to draw the selection. */
void ARTSHUD::CheckForInput()
{
	/* If left mouse was pressed. */
	if (PC->WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		/* Show the selection box. */
		ShowSelectionBox();
	}

	/* If left mouse was released. */
	if (PC->WasInputKeyJustReleased(EKeys::LeftMouseButton))
	{
		
		//Store mouse position when mouse is released
		FVector2D NewMousePos;
		PC->GetMousePosition(NewMousePos.X, NewMousePos.Y);
		
		//If we dragged a selection box instead of just clicked
		if (!StartPos.Equals(NewMousePos, 1))
		{
			// Always deselect before selecting units!
			ARTSCameraController::DeselectUnits();
			AmachinesGameMode* GameMode = (AmachinesGameMode*)GetWorld()->GetAuthGameMode();
			GameMode->OnSelect.Broadcast();
		}

		/* Hide the selection box. */
		HideSelectionBox();
	}
}

/* Draws the selection box if the left mouse button is held. */
void ARTSHUD::DrawHUD()
{	
	if (bDrawSelectionBox)
	{
		DrawSelectionBox();
	}
}

/* Draws a box to display bounds of a unit selection. */
void ARTSHUD::DrawSelectionBox()
{
	//Get mouse position.
	FVector2D MousePos;
	PC->GetMousePosition(MousePos.X, MousePos.Y);

	//Draw the selection box.
	DrawRect(FLinearColor(255, 0, 0, .25f), StartPos.X, StartPos.Y, MousePos.X - StartPos.X, MousePos.Y - StartPos.Y);

	//Store rect of selection box.
	SelectionBox = new Rect(StartPos.X, StartPos.Y, MousePos.X - StartPos.X, MousePos.Y - StartPos.Y);
}

/* Sets the selection box to be drawn. */
void ARTSHUD::ShowSelectionBox()
{
	// Store the start position where the player clicked.
	PC->GetMousePosition(StartPos.X, StartPos.Y);

	// Now draw the selection box every frame until mouse is released.
	bDrawSelectionBox = true;
}

/* Sets the selection box to be hidden. */
void ARTSHUD::HideSelectionBox()
{
	bDrawSelectionBox = false;
}

/* Checks if the selection rect contains a given ScreenPoint. */
bool ARTSHUD::SelectionContainsPoint(FVector2D ScreenPoint)
{
	return SelectionBox->Contains(ScreenPoint);
}

