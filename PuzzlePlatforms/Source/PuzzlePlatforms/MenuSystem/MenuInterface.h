// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLEPLATFORMS_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//virtual void Host() = 0;
	//classes using this interface must implement ReactToHighNoon

	virtual void Host(FString ServerName) = 0;  // Equal zero ( = 0; ) means it is a pure 
	virtual void Join(uint32 Index) = 0; // Both methods are virtual because we want them to be implemente by sub-classes and in our case it is the game instance.
	virtual void LoadMainMenu() = 0;
	virtual void ExitGame() = 0;
	virtual void RefreshingServerList() = 0;
};
