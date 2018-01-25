// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "Components/BoxComponent.h"


AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
		
	MoveFactor = 200.0f;

	SetMobility(EComponentMobility::Movable);
}


void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// This If will run only if HasAuthority returns TRUE And it will return True only when It is on the server , if it is a client it retunrs false.
	if (HasAuthority()) 
	{
		FVector Location = GetActorLocation();
		auto ActorForwardVector = GetActorForwardVector();
		Location += ActorForwardVector * MoveFactor * DeltaSeconds;
		SetActorLocation(Location);
	}
	else
	{
		// THIS CODE WILL RUN ON THE CLIENT 
		SetActorHiddenInGame(true);
	}
	
}