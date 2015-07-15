// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DStaticLibrary.h"
#include "Colorable.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UColorable : public UInterface
{
	GENERATED_UINTERFACE_BODY()

public:

	DTypes::DCOLOR DColor;
};

class IColorable
{
	GENERATED_IINTERFACE_BODY()

public:

	DTypes::DCOLOR DColor;

};