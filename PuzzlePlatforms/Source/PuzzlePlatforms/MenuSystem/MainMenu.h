// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"

#include "MenuInterface.h"

#include "MainMenu.generated.h"


USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	int32 Ping;
	FString HostUsername;
	FString PlayerName;
};
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
public:

	UMainMenu(const FObjectInitializer & ObjectInitializer);

	void SetServerList(TArray<FServerData> ServerNames);
	void SelectIndex(uint32 Index);

protected:
	virtual bool Initialize() override;
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConfirmJoinServerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* RefreshServerListButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConfirmHostAServerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostServerCancelButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* ServerNameTextBox;


	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostAServerMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	TSubclassOf<class UUserWidget> ServerRowClass;


	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void RefreshServerList();

	UFUNCTION()
	void OpenHostAServerMenu();

	UFUNCTION()
	void ReturnToMainMenu();
	
	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void QuitClicked();


	void UpdateChildren();

	TOptional<uint32> SelectedIndex;


};
