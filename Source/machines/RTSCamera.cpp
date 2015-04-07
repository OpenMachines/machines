// Fill out your copyright notice in the Description page of Project Settings.

#include "machines.h"
#include "RTSCamera.h"


// Sets default values
ARTSCamera::ARTSCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARTSCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTSCamera::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//UE_LOG(LogTemp, Warning, TEXT("%f"));
	//GetInputAxisValue("MoveForward");
}

// Called to bind functionality to input
void ARTSCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	//Super::SetupPlayerInputComponent(InputComponent);

	//check(InputComponent);
	//InputComponent->BindAxis("MoveForward", this, &ARTSCamera::MoveForward);
	//InputComponent->BindAxis("MoveRight", this, &ARTSCamera::MoveRight);
}

void ARTSCamera::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%f"));
		
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ARTSCamera::MoveRight(float Value)
{
	//float input = InputComponent->GetAxisValue("MoveRight");

	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

