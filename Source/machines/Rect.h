
#pragma once

#include "machines.h"
#include "Vector2D.h"

/**
Represents a 2D rectangle usually used in GUI features.
*/
struct Rect{

	float X;
	float Y;
	float Width;
	float Height;

	/* Default constructor. */
	Rect(){

	}

	/* Creates a rect with given values. */
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

	/* Check if the rect on contains a given point. */
	bool Contains(FVector2D ScreenPosition)
	{
		float RectLeft = X;
		float RectTop = Y;
		float RectRight = X + Width;
		float RectBottom = Y + Height;

		float temp;

		//If negative bottom, flip with top and make positive
		if (RectBottom < RectTop){
			temp = RectTop;
			RectTop = FMath::Abs(RectBottom);
			RectBottom = FMath::Abs(temp);
		}

		//If negative right, flip with left and make positive
		if (RectRight < RectLeft){
			temp = RectLeft;
			RectLeft = FMath::Abs(RectRight);
			RectRight = FMath::Abs(temp);
		}

		//Return whether the point is within the positive rect.
		return(ScreenPosition.X >= RectLeft && ScreenPosition.X <= RectRight
			&& ScreenPosition.Y >= RectTop && ScreenPosition.Y <= RectBottom);
	}
};
