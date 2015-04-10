// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "machines.h"
#include "machinesGameMode.h"
#include "RTSCamera.h"
//#include "machinesHUD.h"
//#include "machinesCharacter.h"

AmachinesGameMode::AmachinesGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<ADefaultPawn> PlayerPawnClassFinder(TEXT("Class'/Script/machines.RTSCamera'"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;	

	

//	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("Class'/Script/machines.RTSCameraController'"));
//	PlayerControllerClass = PlayerControllerClassFinder.Class;



	// use our custom HUD class Blueprint'/Game/Blueprints/NewPlayerController.NewPlayerController'
	//HUDClass = AmachinesHUD::StaticClass();
}
 
//void AmachinesGameMode::BeginPlay(){
//	APlayerController* CameraController = PlayerControllerClass->GetDefaultObject<APlayerController>();

	//SpawnDefaultPawnFor(CameraController, PlayerStarts[0]);
	//Super::BeginPlay();
	//AController* CameraController = PlayerControllerClass->GetDefaultObject<AController>();

	//ARTSCamera* CameraPawn = (ARTSCamera*)GetWorld()->SpawnActor(DefaultPawnClass);

	//ARTSCamera* CameraPawn = SpawnDefaultPawnFor(CameraController, PlayerStarts[0]);//DefaultPawnClass->GetDefaultObject<ADefaultPawn>();

	//APlayerController* CameraController = PlayerControllerClass->GetDefaultObject<APlayerController>();

	//CameraController->SetPawn(CameraPawn);
	//CameraController->
	//CameraController
//}