// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"

void ALobbyGameMode::PostLogin(APlayerController * NewPlayer)
{
	if (!ensure(NewPlayer != nullptr)) return;

	NumOfPlayers = GetNumPlayers();
	if (NumOfPlayers >= 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("DONEKY MONKEY"));
	}
}

void ALobbyGameMode::Logout(AController * Exiting)
{
	--NumOfPlayers;
}
