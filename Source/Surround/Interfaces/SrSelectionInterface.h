// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SrSelectionInterface.generated.h"


/**
 * 
 */

UINTERFACE(Blueprintable)
class SURROUND_API USrSelectionInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class SURROUND_API ISrSelectionInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	/** Called when this actor is selected */
	UFUNCTION(BlueprintNativeEvent)
	bool OnSelectionGained();

	/** Called when this actor is unselected */
	UFUNCTION(BlueprintNativeEvent)
	bool OnSelectionLost(const FVector& NewPosition, AActor* NewActor);

	/** Called when someone claims ownership on this actor */
	UFUNCTION(BlueprintNativeEvent)
	void SetTeamController(AController* Controller);

	/** Called to get ownership of this actor */
	UFUNCTION(BlueprintNativeEvent)
	AController* GetTeamController();
};	
