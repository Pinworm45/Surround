// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interfaces/SrSelectionInterface.h"
#include "Interfaces/SrInputInterface.h"

#include "SrVehicle.generated.h"

UCLASS()
class SURROUND_API ASrVehicle : public APawn, public ISrSelectionInterface, public ISrInputInterface
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	ASrVehicle();



	///////////////////////////////////////////////////////////////////////////
	// Actor inherited

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;



	///////////////////////////////////////////////////////////////////////////
	// Movement

public:

	/** Speed in cm per second */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sr|Vehicle")
	float MaxSpeed = 10.0f;

private:
	/** Stores the last location */
	FVector CurrentLocation = FVector::ZeroVector;


	
	///////////////////////////////////////////////////////////////////////////
	// Input

public:
	UFUNCTION(BlueprintCallable, Category = "Sr|Input")
	bool IsSelected() const { return bIsSelected; }

	/** Called when this actor is selected */
	bool OnSelectionGained_Implementation();

	/** Called when this actor is unselected */
	bool OnSelectionLost_Implementation(const FVector& NewPosition, AActor* NewActor);

	/** Called when someone claims ownership on this actor */
	void SetTeamController_Implementation(AController* Controller);

	/** Called to get ownership of this actor */
	AController* GetTeamController_Implementation();

	/** Called when this actor was tapped */
	void OnInputTap_Implementation();

	/** Called when this actor was hold  */
	void OnInputHold_Implementation();

	/** Called when hold was released for this actor  */
	void OnInputHoldReleased_Implementation(float DownTime);

	/** Called when swipe started with this actor selected */
	void OnInputSwipeStarted_Implementation(const FVector2D& InitialPosition);

	/** Called when swipe updated with this actor selected */
	void OnInputSwipeUpdate_Implementation(const FVector2D& DeltaPosition);

	/** Called when swipe released with this actor selected */
	void OnInputSwipeReleased_Implementation(const FVector2D& FinalPosition, ESwipeDirection SwipeDirection, float DownTime);

	/** If true the vehicle gets an outline effect when selected. Note this is applied to all mesh components. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sr|Input")
	bool bOutlineOnSelect = true;

	/** How far up down the unit bounces when it's selected */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sr|Input")
	float BounceOffsetWhenSelected = 5.0f;

	/** How many times the units bounces per second when it's selected */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sr|Input")
	float BounceRateWhenSelected = 10.0f;

private:
	/** true when selected */
	bool bIsSelected = false;

	/** Internal storage of the time since bouncing started, for example due to selection */
	float BounceTimer = 0.0f;

};
