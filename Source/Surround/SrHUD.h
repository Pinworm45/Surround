// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "SrHUD.generated.h"

/**
 * 
 */


DECLARE_EVENT_TwoParams(AReHUD, FOnVieportSizeChangedEvent, int32, int32)


UCLASS()
class SURROUND_API ASrHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;


	/** Event fired when the viewport size changed */
	FOnVieportSizeChangedEvent OnViewportSizeChangedEvent;

private:
	int32 PreviousCanvasSizeX = 0;
	int32 PreviousCanvasSizeY = 0;
	
};
