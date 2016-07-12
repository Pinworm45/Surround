// Fill out your copyright notice in the Description page of Project Settings.

#include "Surround.h"
#include "SrPlanet.h"


// Sets default values
ASrPlanet::ASrPlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionComponent"));
	if (InteractionComponent)
	{
		InteractionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		InteractionComponent->SetCollisionResponseToChannel(COLLISION_PLANETS, ECollisionResponse::ECR_Overlap);

		InteractionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASrPlanet::OnInteractionSphereBeginOverlap);
		InteractionComponent->OnComponentEndOverlap.AddDynamic(this, &ASrPlanet::OnInteractionSphereEndOverlap);
	}
}

// Called when the game starts or when spawned
void ASrPlanet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASrPlanet::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASrPlanet::OnInteractionSphereBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{


}


void ASrPlanet::OnInteractionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
