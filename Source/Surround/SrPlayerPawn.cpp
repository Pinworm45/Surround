// Fill out your copyright notice in the Description page of Project Settings.

#include "Surround.h"

#include "SrPlayerController.h"
#include "SrPlayerCameraComponent.h"

#include "SrPlayerPawn.h"



ASrPlayerPawn::ASrPlayerPawn()
{
	GetCollisionComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	bAddDefaultMovementBindings = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	if (CapsuleComponent)
	{
		CapsuleComponent->InitCapsuleSize(0.0f, 0.0f);
		
		CapsuleComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
		CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		CapsuleComponent->CanCharacterStepUpOn = ECB_No;
		CapsuleComponent->bShouldUpdatePhysicsVolume = false;
		CapsuleComponent->bCheckAsyncSceneOnMove = false;
		CapsuleComponent->SetCanEverAffectNavigation(false);
		CapsuleComponent->bDynamicObstacle = false;

		SetRootComponent(CapsuleComponent);
	}
	else
	{
		UE_LOG(LogSr, Error, TEXT("Failed to instaniate Capsule Component in %s"), *GetName());

	}

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoomComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	if (CameraBoomComponent)
	{		
		CameraBoomComponent->SetupAttachment(RootComponent);
		CameraBoomComponent->TargetArmLength = 30000.0f; // The camera follows at this distance behind the character	
		CameraBoomComponent->bUsePawnControlRotation = true; // Rotate the arm based on the controller
		CameraBoomComponent->bDoCollisionTest = false; 

	}
	else
	{
		UE_LOG(LogSr, Error, TEXT("Failed to instaniate Camera Boom Component in %s"), *GetName());
	}

	CameraComponent = CreateDefaultSubobject<USrPlayerCameraComponent>("CameraComponent");
	if (CameraComponent)
	{		
		CameraComponent->SetupAttachment(CameraBoomComponent, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
		CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	}
	else
	{
		UE_LOG(LogSr, Error, TEXT("Failed to instaniate Camera Component in %s"), *GetName());
	}

	
}


void ASrPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerController = Cast<ASrPlayerController>(GetController());
	if (PlayerController)
	{
		auto HUD = Cast<ASrHUD>(PlayerController->GetHUD());
		if (HUD)
		{
			HUD->OnViewportSizeChangedEvent.AddUFunction(this, "OnViewportSizeChanged");
		}
	}


	auto World = GetWorld();
	if (World)
	{
		UpdateSpringArmLength(World);
		UpdateWorldToScreenCoef(World);
	}
}


void ASrPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ASrPlayerPawn::Move(float PixelsX)
{
	auto Location = GetActorLocation();
	SetActorLocation(FVector(Location.X - PixelsX * WorldToScreenCoef, Location.Y, Location.Z));
}


void ASrPlayerPawn::SetVisibleHorizontalArea(float Length)
{
	auto World = GetWorld();
	if (World)
	{
		VisibleHorizontalArea = Length;
		UpdateSpringArmLength(World);
		UpdateWorldToScreenCoef(World);
	}
}


void ASrPlayerPawn::UpdateSpringArmLength(UWorld* World)
{
	if (World && CameraComponent && CameraBoomComponent)
	{
		auto Viewport = World->GetGameViewport();
		if (Viewport)
		{
			auto ViewportSize = FVector2D::ZeroVector;
			Viewport->GetViewportSize(ViewportSize);
			CameraBoomComponent->TargetArmLength = 0.5f * VisibleHorizontalArea / FMath::Tan(FMath::DegreesToRadians(CameraComponent->FieldOfView / 2.0f));
			CameraBoomComponent->SocketOffset = FVector(0.0f, 0.0f, (ViewportSize.Y / ViewportSize.X) * VisibleHorizontalArea / 2.0f);
		}
	}
}


void ASrPlayerPawn::UpdateWorldToScreenCoef(UWorld* World)
{
	if (World)
	{
		auto Viewport = World->GetGameViewport();
		if (Viewport)
		{
			auto ViewportSize = FVector2D::ZeroVector;
			Viewport->GetViewportSize(ViewportSize);

			if (!ViewportSize.X == 0)
			{
				WorldToScreenCoef = VisibleHorizontalArea / ViewportSize.X;
			}
			else
			{
				WorldToScreenCoef = 1.0f;
			}
		}
	}
}


void ASrPlayerPawn::UpdateWorldToScreenCoef(UWorld* World, FVector2D ViewportSize)
{
	if (World)
	{
		if (!ViewportSize.X == 0)
		{
			WorldToScreenCoef = VisibleHorizontalArea / ViewportSize.X;
		}
		else
		{
			WorldToScreenCoef = 1.0f;
		}
	}
}




void ASrPlayerPawn::OnViewportSizeChanged(int32 X, int32 Y)
{
	auto World = GetWorld();
	if (World)
	{
		UpdateSpringArmLength(World);
		UpdateWorldToScreenCoef(World, FVector2D(X, Y));
	}
}