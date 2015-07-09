// Fill out your copyright notice in the Description page of Project Settings.

#include "machines.h"
#include "RTSUnit.h"
#include "RTSHUD.h"
#include "machinesGameMode.h"
#include "RTSCameraController.h"
#include "KismetMathLibrary.generated.h"


#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)


/* Sets default values. */
ARTSUnit::ARTSUnit(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StaticMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMeshComponent"));
	StaticMeshComponent->AttachParent = GetRootComponent();

	static ConstructorHelpers::FClassFinder<AProjectile> ProjectileClassFinder(TEXT("Class'/Script/machines.Projectile'"));
	ProjectileClass = ProjectileClassFinder.Class;

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	StaticMeshComponent->SetStaticMesh(MeshObj.Object);
		
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunOffset = FVector(100.0f, 30.0f, 10.0f);
}

/* Called when the game starts or when spawned. */
void ARTSUnit::BeginPlay()
{
	Super::BeginPlay();

	BindToSelectionAction(); 

	SetRotationValues();

	PC = GetWorld()->GetFirstPlayerController();

	StaticMeshComponent->SetRelativeLocation(FVector(0, 0, 0));

}

/* Sets proper rotation values for the character. */
void ARTSUnit::SetRotationValues()
{
	UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();

	CharacterMovement->bOrientRotationToMovement = true;
	CharacterMovement->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	bUseControllerRotationYaw = false;
	CharacterMovement->bUseControllerDesiredRotation = false;

	DefaultAttackSpeed = 1.0f;

	CurrentAttackSpeed = DefaultAttackSpeed;

}

/* Called every frame. */
void ARTSUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (State)
	{
		/* Move unit to destination. */
		case UnitAction::Move:
			CurrentDistance = FVector::Dist(CurrentDestination, GetActorLocation());
			if (CurrentDistance < StopDistance)
			{
				State = UnitAction::Idle;
			}
			break;
		/* Tell unit to attack target. */
		case UnitAction::Attack:
			if (Target != NULL)
			{
				CurrentDistance = FVector::Dist(Target->GetActorLocation(), GetActorLocation());

				float Cooldown = 1.0f / CurrentAttackSpeed;

				if (CurrentDistance < AttackDistance)
				{
					GetController()->StopMovement();
					if (GetWorld()->GetTimeSeconds() >= NextTimeToAttack)
					{
						OnFire();
						NextTimeToAttack = GetWorld()->GetTimeSeconds() + Cooldown;
					}
				}

				FRotator LookRot = (Target->GetActorLocation() - GetActorLocation()).Rotation();

				FRotator NewRot = FMath::RInterpTo(GetActorRotation(), LookRot, DeltaTime, CharacterMovement->RotationRate.Yaw * DeltaTime);

				SetActorRelativeRotation(NewRot);
			}
			break;
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

	/* Find screen coordinates of the unit. */
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

	/* If the selection box contains the screen postion: */
	if (ARTSHUD::SelectionContainsPoint(MyResult)){

		// Select this unit, and leave possibility to select others.
		Select();
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
bool ARTSUnit::PerformCommand()
{
	FHitResult Hit = GetMouseWorldCoordinates();
	if (Hit.bBlockingHit)
	{
		if (Hit.Actor != NULL)
		{
			ARTSUnit* unit = Cast<ARTSUnit>(Hit.GetActor());

			if (unit != NULL)
			{
				Attack(unit);
				return true;
			}
		}
			
		// We hit something, move there
		Move(Hit.ImpactPoint);
		return true;
	}
	State = UnitAction::Idle;
	return false;
}

/* Sets the unit to attack a target unit. */
void ARTSUnit::Attack(AActor* Target)
{
	UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();

	CurrentDistance = FVector::Dist(Target->GetActorLocation(), GetActorLocation());

	if (CurrentDistance > AttackDistance)
	{
		NavSys->SimpleMoveToActor(GetController(), Target);
	}
	
	this->Target = Target;
	State = UnitAction::Attack;
}

/* Moves the unit to a target position. */
void ARTSUnit::Move(const FVector DestLocation)
{
	CurrentDestination = DestLocation;
	UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
	//float const Distance = FVector::Dist(DestLocation, GetActorLocation());
	CurrentDistance = FVector::Dist(DestLocation, GetActorLocation());

	// We need to issue move command only if far enough in order for walk animation to play correctly
	if (NavSys && (CurrentDistance > StopDistance))
	{
		State = UnitAction::Move;
		NavSys->SimpleMoveToLocation(GetController(), DestLocation);
	}
}

/* Binds selection action to CheckForSelection function. */
void ARTSUnit::BindToSelectionAction()
{
	AmachinesGameMode* GameMode = (AmachinesGameMode*)GetWorld()->GetAuthGameMode();
	GameMode->OnSelect.AddDynamic(this, &ARTSUnit::CheckForSelection);
}

/* Selects the unit and deselects others. */
void ARTSUnit::SelectExclusive()
{
	// Always deselect before selecting a single unit!
	ARTSCameraController::DeselectUnits();

	// Select the unit.
	ARTSCameraController::SelectUnit(this);
}

/* Selects the unit. */
void ARTSUnit::Select()
{
	ARTSCameraController::SelectUnit(this);
}

/* Fires a projectile. */
void ARTSUnit::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
	}

	// try and play the sound if specified
	//if (FireSound != NULL)
	//{
	//	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	//}

	//// try and play a firing animation if specified
	//if (FireAnimation != NULL)
	//{
	//	// Get the animation object for the arms mesh
	//	UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
	//	if (AnimInstance != NULL)
	//	{
	//		AnimInstance->Montage_Play(FireAnimation, 1.f);
	//	}
	//}
}