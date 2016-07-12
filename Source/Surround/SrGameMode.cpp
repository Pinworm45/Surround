// Fill out your copyright notice in the Description page of Project Settings.

#include "Surround.h"

#include "SrHUD.h"
#include "SrPlayerController.h"
#include "SrPlayerPawn.h"

#include "SrGameMode.h"




ASrGameMode::ASrGameMode()
{
	HUDClass = ASrHUD::StaticClass();
	PlayerControllerClass = ASrPlayerController::StaticClass();
	SpectatorClass = ASrPlayerPawn::StaticClass();
	DefaultPawnClass = ASrPlayerPawn::StaticClass();
}


void ASrGameMode::RestartPlayer(AController* NewPlayer)
{
	AActor* const StartSpot = FindPlayerStart(NewPlayer);
	if (StartSpot)
	{
		// initialize and start it up
		InitStartSpot(StartSpot, NewPlayer);

		ASrPlayerController* const NewPlayerController = Cast<ASrPlayerController>(NewPlayer);
		if (NewPlayerController)
		{
			NewPlayerController->SetInitialLocationAndRotation(StartSpot->GetActorLocation(), StartSpot->GetActorRotation());
		}
	}
	else
	{
		UE_LOG(LogSr, Warning, TEXT("Player start not found, failed to restart player."));
	}
}

void ASrGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->GameUserSettings->SetVSyncEnabled(true);
		GEngine->GameUserSettings->ApplySettings(true);
	}
}
