// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "PuzzlePlatformsGameInstance.h"
#include "Kismet/GameplayStatics.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;
	
	if (!ensure(HostButton != nullptr)) return false;


	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	

	return true;

}

void UMainMenu::HostServer()
{
	/*UPuzzlePlatformsGameInstance* GameInstance = Cast<UPuzzlePlatformsGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!ensure(GameInstance != nullptr)) return ;
	GameInstance->Host();*/

	UE_LOG(LogTemp, Warning, TEXT("I am Gonna host a server"));
}
