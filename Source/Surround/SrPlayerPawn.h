// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpectatorPawn.h"

#include "SrHUD.h"

#include "SrPlayerPawn.generated.h"

/**
 * 
 */
UCLASS()
class SURROUND_API ASrPlayerPawn : public ASpectatorPawn
{
	GENERATED_BODY()
	
	///////////////////////////////////////////////////////////////////////////
	// Actor inherited

public:
	ASrPlayerPawn();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	///////////////////////////////////////////////////////////////////////////
	// Movement

public:
	void Move(float PixelsX);


	///////////////////////////////////////////////////////////////////////////
	// Camera

public:
	/** The visible horizontal area in meters */
	UFUNCTION(BlueprintCallable, Category = "Sr|Camera")
	void SetVisibleHorizontalArea(float Length);

	/** Calculates the ideal lenght of the springarm, call whenever the viewport size changed */
	void UpdateSpringArmLength(UWorld* World);

	/** Calculates the world to screen coefficient for intuitive swiping, call on fov or viewport size changes*/
	void UpdateWorldToScreenCoef(UWorld* World);

	/** Calculates the world to screen coefficient for intuitive swiping, call on fov or viewport size changes*/
	void UpdateWorldToScreenCoef(UWorld* World, FVector2D ViewportSize);


private:
	/** The visible horizontal area on screen */
	float VisibleHorizontalArea = 1000.0f;

	/** Coefficient between pixels and Screen */
	float WorldToScreenCoef = 1.0f;

	/** Called whenever the viewport size changed */
	UFUNCTION()
	void OnViewportSizeChanged(int32 X, int32 Y);

	///////////////////////////////////////////////////////////////////////////
	// Components
public:
	FORCEINLINE class USrPlayerCameraComponent* const GetCameraComponent() const { return CameraComponent; }

	FORCEINLINE class USpringArmComponent* const GetCameraBoomComponent() const { return CameraBoomComponent; }

	FORCEINLINE UCapsuleComponent* const GetCapsuleComponent() const { return CapsuleComponent; }



private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sr|Camera", meta = (AllowPrivateAccess = "true"))
	class USrPlayerCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sr|Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoomComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
};
