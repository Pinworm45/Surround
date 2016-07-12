// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "SrPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SURROUND_API ASrPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	///////////////////////////////////////////////////////////////////////////
	// AActor inherited

	ASrPlayerController();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;



	///////////////////////////////////////////////////////////////////////////
	// Input

public:
	FORCEINLINE void SetCanMoveCamera(bool bMovable) { bCanMoveCamera = bMovable;	}
	FORCEINLINE bool GetCanMoveCamera(bool bMovable) const { return bCanMoveCamera; }

private:
	bool bCanMoveCamera = true;



	///////////////////////////////////////////////////////////////////////////
	// Input

public:
	/** Gets the friendly target at this screen location or null if none present */
	UFUNCTION(BlueprintCallable, Category = "Sr|Input")
	AActor* GetFriendlyTargetUnderCursor(const FVector2D& ScreenPoint, FVector& WorldImpactPoint) const;

	void SetSelectedActor(AActor* NewSelectedActor, const FVector& NewPosition);

	void OnTapPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime);
	void OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime);
	void OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);

	/** TODO: The area at the borders of the screen that cause continuous scrolling in pixels */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sr|Input")
	int32 EdgeScrollMargin = 30;


private:
	/** Custom input handler. */
	UPROPERTY()
	class USrInput* InputHandler = nullptr;

	AActor* SelectedActor = nullptr;

	/** The initial Anchor Position when swiping */
	FVector2D InitialAnchorPosition = FVector2D::ZeroVector;

	/** The last anchor position when swiping */
	FVector2D LastScreenPosition = FVector2D::ZeroVector;



	///////////////////////////////////////////////////////////////////////////
	// Optimizations

private:
	/** Cached reference to the pawn */
	class ASrPlayerPawn* Pawn = nullptr;

};
