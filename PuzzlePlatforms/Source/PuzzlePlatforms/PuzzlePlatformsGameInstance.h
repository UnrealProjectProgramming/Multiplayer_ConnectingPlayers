// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"


#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:

	UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer);
	void Init();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void LoadMenuWidget();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void LoadPauseMenu();

	UFUNCTION(Exec)
	void Host() override;
	
	UFUNCTION(Exec)
	void Join(FString Address) override;

	virtual void LoadMainMenu() override;

	virtual void ExitGame() override;

private:
	TSubclassOf<class UUserWidget> MenuClass;

	class UMainMenu* Menu;
	
	TSubclassOf<class UUserWidget> InGameMenuClass;

	void OnCreateSessionComplete(FName SessionName, bool Success);

	void OnDestroySessionComplete(FName SessionName, bool Success);

	void CreateSession();
	IOnlineSessionPtr SessionInterface; // we can't forward declear this bvecause it will need a pointer and it is interface.
};
