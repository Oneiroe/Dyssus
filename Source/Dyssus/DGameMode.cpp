// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "DGameMode.h"

ADGameMode::ADGameMode(const class FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("/Game/FirstPersonBP/Blueprints/BP_DCharacter"));
	if (PlayerPawnObject.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnObject.Class;
	}
}

