// Fill out your copyright notice in the Description page of Project Settings.

#include "Surround.h"

#include "SrTypes.h"
#include "SrInput.h"

#include "SrPlayerPawn.h"
#include "Interfaces/SrSelectionInterface.h"
#include "Interfaces/SrInputInterface.h"

#include "SrPlayerController.h"


ASrPlayerController::ASrPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

}



void ASrPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASrPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputHandler = NewObject<USrInput>(this, "InputHandler");
	if (InputHandler)
	{
		BIND_1P_ACTION(InputHandler, EGameKey::Tap, IE_Pressed, &ASrPlayerController::OnTapPressed);
		BIND_1P_ACTION(InputHandler, EGameKey::Hold, IE_Pressed, &ASrPlayerController::OnHoldPressed);
		BIND_1P_ACTION(InputHandler, EGameKey::Hold, IE_Released, &ASrPlayerController::OnHoldReleased);
		BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Pressed, &ASrPlayerController::OnSwipeStarted);
		BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Repeat, &ASrPlayerController::OnSwipeUpdate);
		BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Released, &ASrPlayerController::OnSwipeReleased);
		BIND_2P_ACTION(InputHandler, EGameKey::SwipeTwoPoints, IE_Pressed, &ASrPlayerController::OnSwipeTwoPointsStarted);
		BIND_2P_ACTION(InputHandler, EGameKey::SwipeTwoPoints, IE_Repeat, &ASrPlayerController::OnSwipeTwoPointsUpdate);
		BIND_2P_ACTION(InputHandler, EGameKey::Pinch, IE_Pressed, &ASrPlayerController::OnPinchStarted);
		BIND_2P_ACTION(InputHandler, EGameKey::Pinch, IE_Repeat, &ASrPlayerController::OnPinchUpdate);
	}
	else
	{
		UE_LOG(LogSr, Error, TEXT("Failed to instaniate InputHandler in %s"), *GetName());
	}


}


void ASrPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Pawn = Cast<ASrPlayerPawn>(GetSpectatorPawn());
	check(Pawn->IsA(ASrPlayerPawn::StaticClass())); // Don't override this with non SrPlayerPawn based classes.
	if (Pawn)
	{
		Pawn->SetActorRotation(this->GetControlRotation());
		Pawn->SetActorLocation(this->GetSpawnLocation());
	}

	FSlateApplication::Get().SetAllUserFocusToGameViewport();

	bShowMouseCursor = true;
}


void ASrPlayerController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	if (!bGamePaused && PlayerInput && InputHandler)
	{
		InputHandler->UpdateDetection(DeltaTime);
	}

	Super::ProcessPlayerInput(DeltaTime, bGamePaused);
}


void ASrPlayerController::SetSelectedActor(AActor* NewSelectedActor, const FVector& NewPosition)
{
	if (SelectedActor != NewSelectedActor)
	{
		// attempt to unselect current selection
		auto const OldSelection = SelectedActor;
		if (OldSelection && OldSelection->Implements<USrSelectionInterface>())
		{
			if (ISrSelectionInterface::Execute_OnSelectionLost(OldSelection, NewPosition, NewSelectedActor))
			{
				SelectedActor = nullptr;
			}
		}

		if (!SelectedActor)
		{
			// attempt to select new selection
			if (NewSelectedActor && NewSelectedActor->Implements<USrSelectionInterface>())
			{
				if (ISrSelectionInterface::Execute_OnSelectionGained(NewSelectedActor))
				{
					SelectedActor = NewSelectedActor;
				}
			}
		}
	}
}


AActor* ASrPlayerController::GetFriendlyTargetUnderCursor(const FVector2D& ScreenPoint, FVector& WorldImpactPoint) const
{
	FHitResult Hit;
	if (GetHitResultAtScreenPosition(ScreenPoint, COLLISION_WEAPON, true, Hit))
	{
		auto HitActor = Hit.GetActor();
		if (HitActor && HitActor->Implements<USrSelectionInterface>())
		{
			if (this == ISrSelectionInterface::Execute_GetTeamController(HitActor))
			{
				WorldImpactPoint = Hit.ImpactPoint;
				return Hit.GetActor();
			}
		}
	}

	return nullptr;
}


void ASrPlayerController::OnTapPressed(const FVector2D& ScreenPosition, float DownTime)
{
	FVector WorldPosition(0.f);
	AActor* const HitActor = GetFriendlyTargetUnderCursor(ScreenPosition, WorldPosition);

	SetSelectedActor(HitActor, WorldPosition);

	if (HitActor && HitActor->Implements<USrInputInterface>())
	{
		ISrInputInterface::Execute_OnInputTap(HitActor);

	}
}


void ASrPlayerController::OnHoldPressed(const FVector2D& ScreenPosition, float DownTime)
{
	FVector WorldPosition(0.0f);
	AActor* const HitActor = GetFriendlyTargetUnderCursor(ScreenPosition, WorldPosition);

	SetSelectedActor(HitActor, WorldPosition);

	if (HitActor && HitActor->Implements<USrInputInterface>())
	{
		ISrInputInterface::Execute_OnInputHold(HitActor);
	}
}


void ASrPlayerController::OnHoldReleased(const FVector2D& ScreenPosition, float DownTime)
{
	if (SelectedActor && SelectedActor->Implements<USrInputInterface>())
	{
		ISrInputInterface::Execute_OnInputHoldReleased(SelectedActor, DownTime);
	}

}


void ASrPlayerController::OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime)
{
	InitialAnchorPosition = AnchorPosition;
	LastScreenPosition = AnchorPosition;

	FVector WorldPosition = FVector::ZeroVector;
	auto HitActor = GetFriendlyTargetUnderCursor(AnchorPosition, WorldPosition);
	if (HitActor)
	{
		SetSelectedActor(HitActor, WorldPosition);
		if (HitActor->Implements<USrInputInterface>())
		{
			ISrInputInterface::Execute_OnInputSwipeStarted(HitActor, AnchorPosition);
		}
	}
}


void ASrPlayerController::OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime)
{
	if (!SelectedActor && Pawn)
	{
		Pawn->Move(ScreenPosition.X - LastScreenPosition.X);	
	}
	else
	{
		if (SelectedActor->Implements<USrInputInterface>())
		{
			ISrInputInterface::Execute_OnInputSwipeUpdate(SelectedActor, ScreenPosition - LastScreenPosition);
		}
	}

	LastScreenPosition = ScreenPosition;
}

void ASrPlayerController::OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime)
{
	if (SelectedActor && SelectedActor->Implements<USrInputInterface>())
	{
		if (FMath::Abs(InitialAnchorPosition.X - LastScreenPosition.X) > FMath::Abs(InitialAnchorPosition.Y - LastScreenPosition.Y)) // mostly horizontally
		{
			if (InitialAnchorPosition.X < LastScreenPosition.X) // to the left
			{
				ISrInputInterface::Execute_OnInputSwipeReleased(SelectedActor, ScreenPosition, ESwipeDirection::Left, DownTime);
			}
			else // to the right
			{
				ISrInputInterface::Execute_OnInputSwipeReleased(SelectedActor, ScreenPosition, ESwipeDirection::Right, DownTime);
			}
		}
		else // mostly vertically
		{
			if (InitialAnchorPosition.Y > LastScreenPosition.Y) // up
			{
				ISrInputInterface::Execute_OnInputSwipeReleased(SelectedActor, ScreenPosition, ESwipeDirection::Up, DownTime);
			}
			else // down
			{
				ISrInputInterface::Execute_OnInputSwipeReleased(SelectedActor, ScreenPosition, ESwipeDirection::Down, DownTime);
			}
		}
	}	
}


void ASrPlayerController::OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	// forward this as if it was a single finger
	OnSwipeStarted((ScreenPosition1 + ScreenPosition2) * 0.5f, DownTime);
}


void ASrPlayerController::OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	// forward this as if it was a single finger
	OnSwipeUpdate((ScreenPosition1 + ScreenPosition2) * 0.5f, DownTime);
}


void ASrPlayerController::OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime)
{
	// unused for now
}


void ASrPlayerController::OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	// unused for now
}


