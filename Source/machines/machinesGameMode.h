// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "machinesGameMode.generated.h"

/* Used as an event that occurs once the selection box is hidden, and units should be selected. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSelectionAction);

/**
 * Default GameMode class.
 */
UCLASS()
class MACHINES_API AmachinesGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	/* Event used to tell every unit when to check for a selection. */
	FSelectionAction OnSelect;

	/* Sets default class values. */
	AmachinesGameMode(const FObjectInitializer& ObjectInitializer);
};
