// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "Components/BoxComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"


AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
		
	Speed = 200.0f;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		SetReplicates(true); // both of SetReplicates Runs only on the SERVER and it sends to the client to update the Replicate.
		SetReplicateMovement(true);
	} 

    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation); // get the global target location instead of the current relative location
	GlobalStartLocation = GetActorLocation(); // This is the initial Actor location
}


void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ActiveTriggers > 0)
	{
		// This If will run only if HasAuthority returns TRUE And it will return True only when It is on the server , if it is a client it retunrs false.
		if (HasAuthority())
		{
			// THIS CODE WILL RUN ON THE SERVER
			FVector Location = GetActorLocation(); // the actor location being updated every single Tick
			float JournyLength = (GlobalTargetLocation - GlobalStartLocation).Size(); // The length of the journy  
			float JournyTravelled = (Location - GlobalStartLocation).Size(); // the legnth of the travelled journy

			if (JournyTravelled >= JournyLength)
			{
				//THIS IS MANUAL SWAPING WITHOUT USING THE FUNCTION
				//FVector Swap = GlobalStartLocation;
				//GlobalStartLocation = GlobalTargetLocation;
				//GlobalTargetLocation = Swap;
				Swap(GlobalStartLocation, GlobalTargetLocation);
			}

			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			Location += Direction * Speed * DeltaSeconds;
			SetActorLocation(Location);
		}
		else
		{
			// THIS CODE WILL RUN ON THE CLIENT 
		}
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}



