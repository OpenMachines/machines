// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Projectile.h"
#include "RTSUnit.generated.h"

enum class UnitAction {Move, Attack, Idle, Patrol, Guard};

/*
Base class used for all units.
*/
UCLASS()
class MACHINES_API ARTSUnit : public ACharacter
{
	GENERATED_BODY()

public:	
	
	//Unit properties
	/* Distance at which the unit should stop moving. */
	const float StopDistance = 120.0f;

	/* Stores current state. */
	UnitAction State = UnitAction::Idle;

	/* Stores all possible actions for a unit. */
	TArray<UnitAction*> AvailableCommands;

	/* Display name of a unit. */
	FString Name;

	/* Current health of a unit. */
	float CurrentHealth;

	/* Default health of a unit. */
	float DefaultHealth;

	/* Current armor of a unit. */
	float CurrentArmor;

	/* Default armor of a unit. */
	float DefaultArmor;

	/* Current damage of a unit. */
	float CurrentDamage;

	/* Default damage of a unit. */
	float DefaultDamage;

	/* Current movement speed of a unit. */
	float CurrentSpeed;

	/* Default movement speed of a unit. */
	float DefaultSpeed;

	/* Current attack speed of a unit. */
	float CurrentAttackSpeed;

	/* Default attack speed of a unit. */
	float DefaultAttackSpeed;

	/* Is the unit selected? */
	bool bIsSelected;

	/* Where the unit is currently headed. */
	FVector CurrentDestination;

	/* Distance between unit and its destination. */
	float CurrentDistance;

	/* Temporary sphere visual representation. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UStaticMeshComponent* StaticMeshComponent;

	/* Sets default values for this character's properties */
	ARTSUnit(const FObjectInitializer& ObjectInitializer);

	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;
	
	/* Called every frame. */
	virtual void Tick( float DeltaSeconds ) override;

	/* Called to bind functionality to input. */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	/* Temporary sphere visual representation. */
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TSubclassOf<class AProjectile> ProjectileClass;

	/* Selects the unit and deselects others. */
	UFUNCTION()
	void SelectExclusive();

	/* Fires a projectile. */
	void OnFire();

	/* Selects the unit. */
	UFUNCTION()
	void Select();

	/* Binds the selection function to the OnSelect delegate. */
	UFUNCTION()
	void BindToSelectionAction();

	/* Moves to mouse cursor. False if there is nothing to move to. */
	UFUNCTION()
	bool PerformCommand();

private:

	/* Player Controller. */
	APlayerController* PC;

	/* Checks if a unit should be selected. */
	UFUNCTION()
	void CheckForSelection();

	/* Returns the position under the cursor in the world. */
	FHitResult GetMouseWorldCoordinates();	

	/* Moves the unit to a target position. */
	void Move(const FVector DestLocation);
	
};

