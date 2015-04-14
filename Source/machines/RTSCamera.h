// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "RTSCamera.generated.h"


/*
*/

UCLASS()
class MACHINES_API ARTSCamera : public ADefaultPawn
{
	GENERATED_BODY()

	float CameraMaxHeight = 1600;
	float CameraMinHeight = 400;

public:

	// Sets default values for this pawn's properties
	ARTSCamera(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	/** Camera Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* CameraComponent;

	/** Camera Z Angle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraZAngle;

	/** Camera Radius From Pawn Position */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraRadius;

	/** Camera Height Angle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraHeightAngle;

	/** Camera Zoom Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraZoomSpeed;

	/** Camera Radius Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraRadiusMax;

	/** Camera Radius Min */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraRadiusMin;

	/** Camera Movement Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraMovementSpeed;

	/** Camera Scroll Boundary */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraScrollBoundary;

	/** Should the camera move? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		bool bCanMoveCamera;

	private:
		/** Sets up player inputs
		*    @param InputComponent - Input Component
		*/
		void SetupPlayerInputComponent(class UInputComponent* InputComponent);

		//Detect whether camera should move based on cursor at viewport edges
		void MoveCameraEdge(float DeltaTime);

		//Move forward by mouse
		void MoveForward(float direction);

		//Move right by mouse
		void MoveRight(float direction);
	public:
		/** Zooms In The Camera */
		UFUNCTION()
			void ZoomIn();

		/** Zooms Out The Camera */
		UFUNCTION()
			void ZoomOut();

		/** Gets the roatation of the camera with only the yaw value
		* @return - returns a rotator that is (0, yaw, 0) of the Camera
		*/
		UFUNCTION()
			FRotator GetIsolatedCameraYaw();

		/** Moves the camera forward
		* @param direcation - (1.0 for forward, -1.0 for backward)
		*/
		UFUNCTION()
			void MoveCameraForward(float direction);

		/** Moves the camera forward
		* @param direcation - (1.0 for right, -1.0 for left)
		*/
		UFUNCTION()
			void MoveCameraRight(float direction);

		/** Repositions The Camera */
		UFUNCTION()
			void RepositionCamera();

		/** Tick Function, Called Every Frame */
		UFUNCTION()
			virtual void Tick(float deltaSeconds) override;

};
