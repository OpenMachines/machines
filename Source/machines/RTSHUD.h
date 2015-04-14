// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "RTSHUD.generated.h"

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

};

/**
 * 
 */
UCLASS()
class MACHINES_API ARTSHUD : public AHUD
{
	GENERATED_BODY()

public:

	APlayerController* PC;

	static bool SelectionContainsPoint(FVector2D ScreenPosition);

	static bool RectContains(Rect* rect, FVector2D ScreenPosition);

	static TArray<ACharacter*> SelectedUnits;

	static void SelectUnit(ACharacter* Unit);

protected:

	virtual void Tick(float Deltatime) override;

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

private:

	//static Rect* SelectionBox;

	static Rect* SelectionBox;

	bool bDrawSelectionBox = false;

	FVector2D StartPos;

	void CheckForInput();

	void DrawSelectionBox();	

	void ShowSelectionBox();

	void HideSelectionBox();

	
	
};

