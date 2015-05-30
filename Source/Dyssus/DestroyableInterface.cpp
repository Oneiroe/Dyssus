// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "DestroyableInterface.h"

UDestroyableInterface::UDestroyableInterface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void IDestroyableInterface::MyDestroy()
{
}
void IDestroyableInterface::MyDestroy(FVector HitLocation, FVector NormalImpulse)
{
}