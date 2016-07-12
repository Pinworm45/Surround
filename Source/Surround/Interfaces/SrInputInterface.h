// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SrInputInterface.generated.h"

 /**
 * Input interface
 *
 * Interface for actors that can recieve mobile input
 */



UENUM(BlueprintType)
enum class ESwipeDirection : uint8
{
	Up,
	Down,
	Left,
	Right
};



UINTERFACE(Blueprintable)
class SURROUND_API USrInputInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class SURROUND_API ISrInputInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	/** Called when this actor was tapped */
	UFUNCTION(BlueprintNativeEvent, Category = "Sr|Input")
	void OnInputTap();

	/** Called when this actor gets held  */
	UFUNCTION(BlueprintNativeEvent, Category = "Sr|Input")
	void OnInputHold();

	/** Called when hold was released for this actor  */
	UFUNCTION(BlueprintNativeEvent, Category = "Sr|Input")
	void OnInputHoldReleased(float DownTime);

	/** Called when swipe started with this actor selected */
	UFUNCTION(BlueprintNativeEvent, Category = "Sr|Input")
	void OnInputSwipeStarted(const FVector2D& InitialPosition);

	/** Called when swipe updated with this actor selected */
	UFUNCTION(BlueprintNativeEvent, Category = "Sr|Input")
	void OnInputSwipeUpdate(const FVector2D& DeltaPosition);

	/** Called when swipe released with this actor selected */
	UFUNCTION(BlueprintNativeEvent, Category = "Sr|Input")
	void OnInputSwipeReleased(const FVector2D& FinalPosition, ESwipeDirection SwipeDirection, float DownTime);

	

};
