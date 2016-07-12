// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "SrGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SURROUND_API ASrGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ASrGameMode();
	
	/**
	* Handle new player, skips pawn spawning.
	* @param NewPlayer
	*/
	virtual void RestartPlayer(AController* NewPlayer) override;

	virtual void BeginPlay() override;
};
