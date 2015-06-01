// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "DestroyableInterface.h"

UDestroyableInterface::UDestroyableInterface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// TODO Most likely, there's no need for this definition
void IDestroyableInterface::Destroy()
{
}

void UDestroyableInterface::Destroy()
{
}