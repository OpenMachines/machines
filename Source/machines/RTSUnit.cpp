// Fill out your copyright notice in the Description page of Project Settings.

#include "machines.h"
#include "RTSUnit.h"
#include "RTSHUD.h"

// Sets default values
ARTSUnit::ARTSUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//PC = GetWorld()->GetFirstPlayerController();
}

// Called when the game starts or when spawned
void ARTSUnit::BeginPlay()
{
	Super::BeginPlay();

	PC = GetWorld()->GetFirstPlayerController();
}

// Called every frame
void ARTSUnit::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector2D MyResult = FVector2D(0,0);

	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PC->Player);

	if (LocalPlayer != NULL && LocalPlayer->ViewportClient != NULL && LocalPlayer->ViewportClient->Viewport != NULL)
	{
		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
			LocalPlayer->ViewportClient->Viewport,
			GetWorld()->Scene,
			LocalPlayer->ViewportClient->EngineShowFlags)
			.SetRealtimeUpdate(true));

		FVector ViewLocation;
		FRotator ViewRotation;
		FSceneView* SceneView = LocalPlayer->CalcSceneView(&ViewFamily, /*out*/ ViewLocation, /*out*/ ViewRotation, LocalPlayer->ViewportClient->Viewport);

		if (SceneView)
		{
			auto MyWorldPosition = GetActorLocation();
			MyResult;
			SceneView->WorldToPixel(MyWorldPosition, MyResult);
		}
	}

	if (PC->WasInputKeyJustReleased(EKeys::LeftMouseButton))
	{
		if (ARTSHUD::SelectionContainsPoint(MyResult)){
			ARTSHUD::SelectUnit(this);
		}
	}
}

// Called to bind functionality to input
void ARTSUnit::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

