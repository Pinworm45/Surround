// Fill out your copyright notice in the Description page of Project Settings.

#include "Surround.h"

#include "SrVehicle.h"


// Sets default values
ASrVehicle::ASrVehicle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//AIControllerClass = ASrAIController::StaticClass();
}

// Called when the game starts or when spawned
void ASrVehicle::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentLocation = GetActorLocation();
}

// Called every frame
void ASrVehicle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// Movement
	CurrentLocation = CurrentLocation + FVector(MaxSpeed * DeltaTime, 0.0f, 0.0f);
	SetActorLocation(CurrentLocation);

	if (bIsSelected)
	{		
		BounceTimer += DeltaTime;
		FVector LocationUp = FVector(0.0f, 0.0f, BounceOffsetWhenSelected) + CurrentLocation;
		FVector LocationDown = FVector(0.0f, 0.0f, -BounceOffsetWhenSelected) + CurrentLocation;
		SetActorLocation(FMath::Lerp(LocationUp, LocationDown, (FMath::Sin(BounceTimer * BounceRateWhenSelected) + 1.0f ) / 2.0f));
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), FMath::Lerp(LocationUp, Median, FMath::Sin(BounceTimer)).Z));
	}	
}

bool ASrVehicle::OnSelectionGained_Implementation()
{	
	bIsSelected = true;


	if (bOutlineOnSelect)
	{
		TSet<UActorComponent*> ActorComponents = GetComponents();
		for (auto& ComponentIterator : ActorComponents)
		{
			UPrimitiveComponent* HighlightableComponent = Cast<UPrimitiveComponent>(ComponentIterator);
			if (HighlightableComponent)
			{
				HighlightableComponent->SetRenderCustomDepth(true);
			}
		}
	}

	return true; // successfully selected
}

bool ASrVehicle::OnSelectionLost_Implementation(const FVector& NewPosition, AActor* NewActor)
{
	if (bOutlineOnSelect)
	{
		TSet<UActorComponent*> ActorComponents = GetComponents();
		for (auto& ComponentIterator : ActorComponents)
		{
			UPrimitiveComponent* HighlightableComponent = Cast<UPrimitiveComponent>(ComponentIterator);
			if (HighlightableComponent)
			{
				HighlightableComponent->SetRenderCustomDepth(false);
			}
		}
	}

	BounceTimer = 0.0f;
	bIsSelected = false;

	return true; // successfully unselected
}

void ASrVehicle::SetTeamController_Implementation(AController* Controller)
{

}

AController* ASrVehicle::GetTeamController_Implementation()
{
	return nullptr;
}

void ASrVehicle::OnInputTap_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("tapped %s"), *GetName()));
}


void ASrVehicle::OnInputHold_Implementation()
{

}


void ASrVehicle::OnInputHoldReleased_Implementation(float DownTime)
{

}

void ASrVehicle::OnInputSwipeStarted_Implementation(const FVector2D& InitialPosition)
{

}

void ASrVehicle::OnInputSwipeUpdate_Implementation(const FVector2D& DeltaPosition)
{

}


void ASrVehicle::OnInputSwipeReleased_Implementation(const FVector2D& FinalPosition, ESwipeDirection SwipeDirection, float DownTime)
{

}

