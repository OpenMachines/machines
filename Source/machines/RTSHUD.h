// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "RTSUnit.h"
#include "RTSHUD.generated.h"




/**
2D Rectangle
*/
struct Rect{

	float X;
	float Y;
	float Width;
	float Height;

	Rect(){

	}

	Rect(float X, float Y, float Width, float Height)
	{
		this->X = X;
		this->Y = Y;
		this->Width = Width;
		this->Height = Height;
	}

	/* Find area of rectangle. */
	float Area(){
		return Width*Height;
	}

	/* Set all values to zero. */
	void Reset(){
		this->X = 0;
		this->Y = 0;
		this->Width = 0;
		this->Height = 0;
	}
};

/**
Handles camera functions and unit selection. 
In the future, this class will also handle
UI features, such as building and unit options.
 */
UCLASS()
class MACHINES_API ARTSHUD : public AHUD
{
	GENERATED_BODY()

public:		

	/* Stores the main player controller. */
	APlayerController* PC;

	/* Check if the selection box rect contains a given point. */
	static bool SelectionContainsPoint(FVector2D ScreenPosition);

	/* Check if a rect on the screen contains a given point. */
	static bool RectContains(Rect* rect, FVector2D ScreenPosition);

	/* Array of all selected units. */
	static TArray<ARTSUnit*> SelectedUnits;

	/* Select a specified unit. */
	static void SelectUnit(ARTSUnit* Unit);

	/* Deselect all selected units. */
	static void DeselectUnits();

protected:

	/* Called every frame. */
	virtual void Tick(float Deltatime) override;

	/* Draws the HUD. */
	virtual void DrawHUD() override;

	/* Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

private:

	/* Rect of the selection box. */
	static Rect* SelectionBox;

	/* Should the selection box be drawn? */
	bool bDrawSelectionBox = false;

	/* Start position of selection box. */
	FVector2D StartPos;

	/* Check for player mouse input. */
	void CheckForInput();

	/* Draw the selection box. */
	void DrawSelectionBox();	

	/* Set selection box to be drawn. */
	void ShowSelectionBox();

	/* Set the selection box to be hidden. */
	void HideSelectionBox();

};

