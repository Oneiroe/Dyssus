// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "Colorable.h"

UColorable::UColorable(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void IColorable::SetColor(DTypes::DCOLOR dColor)
{

}

DTypes::DCOLOR IColorable::GetColor()
{
	return DTypes::DCOLOR::NONE;
}
