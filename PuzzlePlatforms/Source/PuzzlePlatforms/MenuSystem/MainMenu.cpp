// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::ReturnToMainMenu);
	

	return true;

}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterfaceToSet)
{
	MenuInterface = MenuInterfaceToSet;
}

void UMainMenu::Setup()
{
	this->AddToViewport();
	//GetFirstLocalPlayerController();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;

}

void UMainMenu::Teardown()
{
	UE_LOG(LogTemp, Warning, TEXT("Tearing Down"));
	this->RemoveFromViewport();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!ensure(PlayerController != nullptr)) return;


	FInputModeGameOnly InputModeData;
	
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);

}

void UMainMenu::ReturnToMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}
