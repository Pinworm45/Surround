// Fill out your copyright notice in the Description page of Project Settings.

#include "Surround.h"

#include "SrPlayerController.h"
#include "SrPlayerPawn.h"

#include "SrPlayerCameraComponent.h"





#if WITH_EDITOR
void USrPlayerCameraComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property)
	{
		auto PropertyName = PropertyChangedEvent.Property->GetFName();

		// updating the springarm when the field of view was changed
		if (PropertyName == GET_MEMBER_NAME_CHECKED(USrPlayerCameraComponent, FieldOfView))
		{
			auto PlayerPawn = Cast<ASrPlayerPawn>(GetOwner());
			auto World = GetWorld();
			if (PlayerPawn && World)
			{
				PlayerPawn->UpdateWorldToScreenCoef(World);
				PlayerPawn->UpdateSpringArmLength(World);				
			}
		}
	}
}
#endif
