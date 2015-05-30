// Fill out your copyright notice in the Description page of Project Settings.

#include "machines.h"
#include "RTSCamera.h"


// Initializes camera and sets required values.
ARTSCamera::ARTSCamera(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//Intialize The Camera
	CameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("MainCamera"));

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set Default Camera Values
	CameraRadius = 1000.0f;
	CameraZAngle = 0.0f;
	CameraHeightAngle = 70.0f;
	CameraZoomSpeed = 32.0f;
	CameraRadiusMin = 750.0f;
	CameraRadiusMax = 2000.0f;
	CameraMovementSpeed = 2000.0f;
	CameraScrollBoundary = 25.0f;

	//Follow same location and rotation of root component
	CameraComponent->AttachParent = this->GetRootComponent();

	//Allow camera controls
	bCanMoveCamera = true;

	CameraComponent->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ARTSCamera::BeginPlay()
{
	GetCollisionComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RepositionCamera();
}

// Checks if the player's cursor is at a screen edge
void ARTSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCameraEdge(DeltaTime);	
}

// Binds keyboard camera controls and mouse wheel scroll zoom
void ARTSCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	//Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &ARTSCamera::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARTSCamera::MoveRight);

	//opposite to invert scrolling
	InputComponent->BindAction("MouseWheelUp", IE_Pressed, this, &ARTSCamera::ZoomIn);
	InputComponent->BindAction("MouseWheelDown", IE_Pressed, this, &ARTSCamera::ZoomOut);
}

// Moves camera forward or backward
void ARTSCamera::MoveForward(float direction)
{
	// Do not move if the camera is not allowed to.
	if (!bCanMoveCamera)
		return;

	// Find forward direction
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// Get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * direction;

	// Move with correct direction and speed
	AddMovementInput(Direction, CameraMovementSpeed);
}

// Moves camera left or right
void ARTSCamera::MoveRight(float direction)
{
	// Do not move if the camera is not allowed to.
	if (!bCanMoveCamera)
		return;

	// Find right direction
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// Get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * direction;

	// Move with correct direction and speed
	AddMovementInput(Direction, CameraMovementSpeed);
}

// Zooms the camera in when scrolling down.
void ARTSCamera::ZoomIn()
{
	//Get yaw rotation.
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	//Get Z Axis. 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);

	// Set a temporary vector to current position. 
	FVector newPos = GetActorLocation();

	//Go down on Z axis by 30 units.
	newPos.Z -= 30;

	//Set the new location, clamping the zoom position.
	SetActorLocation(FVector(newPos.X, newPos.Y, FMath::Clamp(newPos.Z, CameraMinHeight, CameraMaxHeight)));
}

// Zooms the camera out when scrolling up.
void ARTSCamera::ZoomOut()
{
	//Get yaw rotation.
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	//Get Z Axis. 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);

	// Set a temporary vector to current position. 
	FVector newPos = GetActorLocation();

	//Go up on Z axis by 30 units.
	newPos.Z += 30;

	//Set the new location, clamping the zoom position.
	SetActorLocation(FVector(newPos.X, newPos.Y, FMath::Clamp(newPos.Z, CameraMinHeight, CameraMaxHeight)));
}

// Resets the camera position to original location
void ARTSCamera::RepositionCamera()
{
	RootComponent->SetWorldLocation(FVector(0, 0, 1600));
	RootComponent->SetRelativeRotation(FRotator(-70, 0, 0));
	CameraComponent->SetRelativeLocation(FVector(0, 0, 0));
}

// Returns yaw value of camera
FRotator ARTSCamera::GetIsolatedCameraYaw()
{
	//Return a FRotator containing (0, CameraYaw, 0)
	return FRotator(0.0f, CameraComponent->ComponentToWorld.Rotator().Yaw, 0.0f);
}

// Detects whether cursor is at edge of viewport. If it is, move camera.
void ARTSCamera::MoveCameraEdge(float DeltaTime){
	//Create variables to hold mouse position and screen size
	FVector2D mousePosition;
	FVector2D viewportSize;

	//Get mouse position and screen size
	UGameViewportClient* gameViewport = GEngine->GameViewport;

	//Make sure viewport exists
	check(gameViewport);
	gameViewport->GetViewportSize(viewportSize);

	//Make sure the viewport has focus(contains the mouse)
	if (gameViewport->IsFocused(gameViewport->Viewport) && gameViewport->GetMousePosition(mousePosition) && bCanMoveCamera)
	{
		//Check if the mouse is at the left or right edge of the screen and move accordingly
		if (mousePosition.X < CameraScrollBoundary)
		{
			MoveRight(-1.0f * DeltaTime);
		}
		else if (viewportSize.X - mousePosition.X < CameraScrollBoundary)
		{
			MoveRight(1.0f * DeltaTime);
		}

		//Check if the mouse is at the top or bottom edge of the screen and move accordingly
		if (mousePosition.Y < CameraScrollBoundary)
		{
			MoveForward(1.0f * DeltaTime);
		}
		else if (viewportSize.Y - mousePosition.Y < CameraScrollBoundary)
		{
			MoveForward(-1.0f * DeltaTime);
		}
	}
}