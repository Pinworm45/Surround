// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "SrPlayerCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class SURROUND_API USrPlayerCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
	
#if WITH_EDITOR
		virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	
	
};
