// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MenuSystem/MenuInterface.h"

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
	void LoadMenu();

	UFUNCTION(Exec)
	void Host();
	
	UFUNCTION(Exec)
	void Join(FString Address);

private:
	TSubclassOf<class UUserWidget> MenuClass;

	class UMainMenu* Menu;
	
};
