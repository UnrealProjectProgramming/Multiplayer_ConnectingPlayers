// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "ServerRow.h"
#include "Components/Widget.h"
#include "Components/TextBlock.h"


UMainMenu::UMainMenu(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MainMenu/WBP_ServerRow"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return; //Pointer to a class object that we can later use to instanciate other objects 
	ServerRowClass = ServerRowBPClass.Class;
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::OpenHostAServerMenu);

	if (!ensure(ConfirmHostAServerButton != nullptr)) return false;
	ConfirmHostAServerButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(RefreshServerListButton != nullptr)) return false;
	RefreshServerListButton->OnClicked.AddDynamic(this, &UMainMenu::RefreshServerList);

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::ReturnToMainMenu);
	
	if (!ensure(HostServerCancelButton != nullptr)) return false;
	HostServerCancelButton->OnClicked.AddDynamic(this, &UMainMenu::ReturnToMainMenu);

	if (!ensure(ConfirmJoinServerButton != nullptr)) return false;
	ConfirmJoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitClicked);


	return true;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		if (!ensure(ServerNameTextBox != nullptr)) return;
		if (ServerNameTextBox->Text.ToString() == "")
		{		
			ServerNameTextBox->HintText = FText::FromString(TEXT("Please Enter A Game Name"));
			return;
		}
		auto ServerName = ServerNameTextBox->GetText().ToString();
		MenuInterface->Host(ServerName);
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);
	if (MenuInterface != nullptr)
	{
		MenuInterface->RefreshingServerList();
	}
}

void UMainMenu::RefreshServerList()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->RefreshingServerList();
	}
}

void UMainMenu::OpenHostAServerMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(HostAServerMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(HostAServerMenu);
}

void UMainMenu::ReturnToMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer()
{

	if (SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index = %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index not set"));
	}
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}


void UMainMenu::SetServerList(TArray<FServerData> ServerNames)
{
	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) return;
	ServerList->ClearChildren();

	uint32 i = 0;

	for (const FServerData& ServerData : ServerNames)
	{
		if (!ensure(ServerRowClass != nullptr)) return;
		UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass);
		if (!ensure(Row != nullptr)) return;
		Row->ServerName->SetText(FText::FromString(ServerData.Name));
		Row->HostUsername->SetText(FText::FromString(ServerData.HostUsername));
		FString FractionText = FString::Printf(TEXT("%d/%d"), ServerData.CurrentPlayers, ServerData.MaxPlayers);
		Row->ConnectionFraction->SetText(FText::FromString(FractionText));
		int32 Ping = ServerData.Ping;
		FString PingAsString = FString::FromInt(Ping);
		Row->PingTextBlock->SetText(FText::FromString(PingAsString));
		Row->Setup(this, i);
		i++;
		ServerList->AddChild(Row);
	}
}


void UMainMenu::QuitClicked()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->ExitGame();
	}
}

void UMainMenu::UpdateChildren()
{
	if (!ensure(ServerList != nullptr)) return;
	int32 NumOfChildren = ServerList->GetChildrenCount();
	for (int32 i = 0; NumOfChildren > i; ++i)
	{
		auto Row = Cast<UServerRow>(ServerList->GetChildAt(i)); 
		if (!ensure(Row != nullptr)) return;
		Row->Selected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i); // Using the short circuit and.

	}
}
