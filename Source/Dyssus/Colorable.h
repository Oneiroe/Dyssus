// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DStaticLibrary.h"
#include "Colorable.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UColorable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IColorable
{
	GENERATED_IINTERFACE_BODY()

	virtual DTypes::DCOLOR GetColor();

	virtual void SetColor(DTypes::DCOLOR dColor);
};