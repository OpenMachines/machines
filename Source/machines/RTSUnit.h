// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "RTSUnit.generated.h"

UCLASS()
class MACHINES_API ARTSUnit : public ACharacter
{
	GENERATED_BODY()

public:	
	
	/* Is the unit selected? */
	bool bIsSelected;

	/* Temporary sphere visual representation. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UStaticMeshComponent* StaticMeshComponent;

	/* Sets default values for this character's properties */
	ARTSUnit(const FObjectInitializer& ObjectInitializer);

	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;
	
	/* Called every frame */
	virtual void Tick( float DeltaSeconds ) override;

	/* Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION()
	void BindToSelectionAction();

private:

	/* Player Controller. */
	APlayerController* PC;

	/* Checks if a unit should be selected. */
	UFUNCTION()
	void CheckForSelection();

	/* Returns the position under the cursor in the world. */
	FHitResult GetMouseWorldCoordinates();

	/* Moves to mouse cursor. False if there is nothing to move to. */
	bool MoveToMouseCursor();

	/* Moves to a given destination. */
	void SetNewMoveDestination(const FVector DestLocation);
};
