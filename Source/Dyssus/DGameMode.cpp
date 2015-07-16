// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "DGameMode.h"
#include "DCharacter.h"

ADGameMode::ADGameMode(const class FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("/Game/Dyssus/Blueprints/BP_DCharacter"));
	if (PlayerPawnObject.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnObject.Class;
	}
}

