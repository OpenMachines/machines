// Fill out your copyright notice in the Description page of Project Settings.

#include "machines.h"
#include "RTSHUD.h"

Rect* ARTSHUD::SelectionBox = new Rect(0, 0, 0, 0);
//TArray<ACharacter*> ARTSHUD::SelectedUnits = new TArray<ACharacter*>();

void ARTSHUD::BeginPlay()
{
	PC = GetWorld()->GetFirstPlayerController();
}

void ARTSHUD::Tick(float Deltatime)
{
	CheckForInput();
}

/* Checks to see if left mouse was pressed or released to draw the selection. */
void ARTSHUD::CheckForInput()
{
	//If left mouse was pressed.
	if (PC->WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		ShowSelectionBox();
	}

	//If left mouse was released.
	if (PC->WasInputKeyJustReleased(EKeys::LeftMouseButton))
	{
		HideSelectionBox();
	}
}

/* */
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
	DrawRect(FLinearColor::Red, StartPos.X, StartPos.Y, MousePos.X - StartPos.X, MousePos.Y - StartPos.Y);

	//Store rect of selection box.
	SelectionBox = new Rect(StartPos.X, StartPos.Y, MousePos.X - StartPos.X, MousePos.Y - StartPos.Y);
}

/* Sets the selection box to be drawn. */
void ARTSHUD::ShowSelectionBox()
{
	//Get the start position where the player clicked.
	PC->GetMousePosition(StartPos.X, StartPos.Y);

	//Now draw the selection box every frame until mouse is released.
	bDrawSelectionBox = true;
}

/* Sets the selection box to be hidden. */
void ARTSHUD::HideSelectionBox()
{
	bDrawSelectionBox = false;
}

void ARTSHUD::SelectUnit(ACharacter* Unit)
{
	//SelectedUnits.Add(Unit);
	UE_LOG(LogTemp, Warning, TEXT("Selected a unit!"));
}

bool ARTSHUD::SelectionContainsPoint(FVector2D ScreenPoint)
{
	//return false;
	return RectContains(SelectionBox, ScreenPoint);
}

/* Checks if a given point is within a given rectangle in screen coordinates. */
bool ARTSHUD::RectContains(Rect* rect, FVector2D ScreenPosition)
{
	//incomplete function; works only for positive

	float RectLeft = rect->X;
	float RectTop = rect->Y;
	float RectRight = rect->X + rect->Width;
	float RectBottom = rect->Y + rect->Height;

	return(ScreenPosition.X >= rect->X && ScreenPosition.X <= RectRight
		&& ScreenPosition.Y >= rect->Y && ScreenPosition.Y <= RectBottom);
}

