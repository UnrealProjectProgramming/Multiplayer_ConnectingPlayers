// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"


#include "Components/Button.h"


#include "MainMenu.h"



void UServerRow::Setup(UMainMenu * InParent, uint32 InIndex)
{
	Index = InIndex;
	Parent = InParent;
	if (!ensure(SelectServerButton != nullptr)) return;
	SelectServerButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked); 

}

void UServerRow::OnClicked()
{
	if (!ensure(Parent != nullptr)) return;
	Parent->SelectIndex(Index);
}
