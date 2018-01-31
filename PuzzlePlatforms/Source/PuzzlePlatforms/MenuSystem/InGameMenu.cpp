// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"

#include "MenuWidget.h"
#include"GameFramework/PlayerController.h"
#include "Components/Widget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelClicked);


	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitClicked);


	return true;
}

void UInGameMenu::CancelClicked()
{
	UInGameMenu::Teardown();
}

void UInGameMenu::QuitClicked()
{
	if (MenuInterface != nullptr)
	{
		Teardown();
		MenuInterface->LoadMainMenu();
	}
}
