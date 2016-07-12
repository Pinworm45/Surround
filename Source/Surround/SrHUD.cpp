// Fill out your copyright notice in the Description page of Project Settings.

#include "Surround.h"
#include "SrHUD.h"




void ASrHUD::DrawHUD()
{
	Super::DrawHUD();

	// broadcast to those who concern if the viewportsize changed
	if (PreviousCanvasSizeX != Canvas->SizeX || PreviousCanvasSizeY != Canvas->SizeY)
	{
		PreviousCanvasSizeX = Canvas->SizeX;
		PreviousCanvasSizeY = Canvas->SizeY;
		OnViewportSizeChangedEvent.Broadcast(Canvas->SizeX, Canvas->SizeY);
	}
}

