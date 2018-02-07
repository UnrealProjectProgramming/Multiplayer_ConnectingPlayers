// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"

#include "Engine/Engine.h"
#include "Classes/GameMapsSettings.h"
#include "Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzlePlatformsGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	NumOfPlayers = GetNumPlayers();
	if (NumOfPlayers >= 2)
	{	//TODO add UI affordance to the countdown.
		GetWorldTimerManager().SetTimer(GameStartTimerHandle, this, &ALobbyGameMode::StartGame, 10.0f);

	}
}

void ALobbyGameMode::Logout(AController * Exiting)
{
	Super::Logout(Exiting);
	--NumOfPlayers;
}

void ALobbyGameMode::StartGame()
{
	auto GameInstance = Cast<UPuzzlePlatformsGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!ensure(GameInstance != nullptr)) return;
	GameInstance->StartSession();
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	bUseSeamlessTravel = true;
	World->ServerTravel("/Game/Maps/Game?listen"); // It is very important to put"?listen" so that the server will be ready for players
												   // to connect to it via command line like we did in the prev lectuers
}
