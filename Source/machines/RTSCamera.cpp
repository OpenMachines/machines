// Fill out your copyright notice in the Description page of Project Settings.

#include "machines.h"
#include "RTSCamera.h"


// Sets default values
ARTSCamera::ARTSCamera(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("MainCamera"));
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ARTSCamera::BeginPlay()
{
	GetCollisionComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent->SetWorldLocation(FVector(0, 0, 1600));
	CameraComponent->SetRelativeLocation(RootComponent->GetComponentLocation());
	CameraComponent->SetRelativeRotation(FRotator(-80, 0, 0));
}

// Called every frame
void ARTSCamera::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	CameraComponent->SetWorldLocation(GetActorLocation());
}

// Called to bind functionality to input
void ARTSCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	//Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &ARTSCamera::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARTSCamera::MoveRight);

	//opposite to invert scrolling
	InputComponent->BindAction("MouseWheelUp", IE_Pressed, this, &ARTSCamera::MoveDown);
	InputComponent->BindAction("MouseWheelDown", IE_Pressed, this, &ARTSCamera::MoveUp);
}

void ARTSCamera::MoveForward(float Value)
{
	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ARTSCamera::MoveRight(float Value)
{
	// find out which way is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// add movement in that direction
	AddMovementInput(Direction, Value);
}

void ARTSCamera::MoveUp()
{
	// find out which way is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);

	// add movement in that direction
	FVector newPos = GetActorLocation();

	newPos.Z += 30;

	//GetMovementComponent()->AddInputVector(Direction * 120, false);

	SetActorLocation(newPos);
}

void ARTSCamera::MoveDown()
{
	// find out which way is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);

	// add movement in that direction
	FVector newPos = GetActorLocation();

	newPos.Z -= 30;

	//GetMovementComponent()->AddInputVector(Direction * -120, false);

	SetActorLocation(newPos);
}