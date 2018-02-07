// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"

#include "Engine/Engine.h"
#include "Classes/GameMapsSettings.h"

void ALobbyGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	NumOfPlayers = GetNumPlayers();
	if (NumOfPlayers >= 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("DONEKY MONKEY"));
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;
		bUseSeamlessTravel = true; 
		World->ServerTravel("/Game/Maps/Game?listen"); // It is very important to put"?listen" so that the server will be ready for players
														// to connect to it via command line like we did in the prev lectuers
	}
}

void ALobbyGameMode::Logout(AController * Exiting)
{
	Super::Logout(Exiting);
	--NumOfPlayers;
}
