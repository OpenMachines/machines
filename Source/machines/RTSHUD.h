// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "machines.h"
#include "GameFramework/HUD.h"
#include "RTSUnit.h"
#include "Rect.h"
#include "RTSHUD.generated.h"


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

