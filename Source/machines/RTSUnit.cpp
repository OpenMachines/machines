// Fill out your copyright notice in the Description page of Project Settings.

#include "machines.h"
#include "RTSUnit.h"
#include "RTSHUD.h"
#include "machinesGameMode.h"

/* Sets default values. */
ARTSUnit::ARTSUnit(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StaticMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMeshComponent"));
	StaticMeshComponent->AttachParent = GetRootComponent();

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	StaticMeshComponent->SetStaticMesh(MeshObj.Object);

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

/* Called when the game starts or when spawned. */
void ARTSUnit::BeginPlay()
{
	Super::BeginPlay();

	BindToSelectionAction();

	PC = GetWorld()->GetFirstPlayerController();
		
	StaticMeshComponent->SetRelativeLocation(FVector(0, 0, 0));
	
}

/* Called every frame. */
void ARTSUnit::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//If selected, then when the player right clicks, move to cursor pos in world space.
	if (PC->WasInputKeyJustReleased(EKeys::RightMouseButton) && bIsSelected)
	{
		MoveToMouseCursor();
	}
}

/* Called to bind functionality to input. */
void ARTSUnit::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

/* After release of left mouse button, check if this unit is within selection box. */ 
void ARTSUnit::CheckForSelection()
{
	UE_LOG(LogTemp, Warning, TEXT("called"));

	FVector2D MyResult = FVector2D(0, 0);

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

	if (ARTSHUD::SelectionContainsPoint(MyResult)){
		ARTSHUD::SelectUnit(this);
	}
}

/* Finds mouse position in world coordinates. */
FHitResult ARTSUnit::GetMouseWorldCoordinates()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	return Hit;
}

/* Moves to mouse cursor position in world coordinates. */
bool ARTSUnit::MoveToMouseCursor(){

	FHitResult Hit = GetMouseWorldCoordinates();
	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
		return true;
	}
	return false;
}

/* Moves to a given destination. */
void ARTSUnit::SetNewMoveDestination(const FVector DestLocation)
{
	UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
	float const Distance = FVector::Dist(DestLocation, GetActorLocation());

	// We need to issue move command only if far enough in order for walk animation to play correctly
	if (NavSys && (Distance > 120.0f))
	{
		NavSys->SimpleMoveToLocation(GetController(), DestLocation);
	}
}

/* Binds selection action to CheckForSelection function. */
void ARTSUnit::BindToSelectionAction()
{
	AmachinesGameMode* GameMode = (AmachinesGameMode*)GetWorld()->GetAuthGameMode();
	GameMode->OnSelect.AddDynamic(this, &ARTSUnit::CheckForSelection);
}