// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ensure(Host != nullptr)) return;
	if (!ensure(Join != nullptr)) return;


}

