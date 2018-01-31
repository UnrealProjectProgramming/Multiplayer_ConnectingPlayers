// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"




void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterfaceToSet)
{
	MenuInterface = MenuInterfaceToSet;
}

void UMenuWidget::Setup()
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

void UMenuWidget::Teardown()
{
	UE_LOG(LogTemp, Warning, TEXT("Tearing Down"));
	this->RemoveFromViewport();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!ensure(PlayerController != nullptr)) return;


	FInputModeGameOnly InputModeData;

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}