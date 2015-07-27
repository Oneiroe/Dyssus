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

	/** Returns the color this colorator will paint with overlapping meshes */
	virtual DTypes::DCOLOR GetColor();

	/** Sets the color this colorator will paint with overlapping meshes */
	virtual void SetColor(DTypes::DCOLOR dColor);
};