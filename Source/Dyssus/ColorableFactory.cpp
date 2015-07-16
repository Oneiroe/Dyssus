// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "ColorableFactory.h"
#include "DStaticLibrary.h"
#include "Colorable.h"
#include "Cube.h"
#include "DBarrier.h"

bool UColorableFactory::CompareColors(AActor* a, AActor* b)
{
	if (!a->Implements<UColorable>() || !b->Implements<UColorable>()) return false;

	return Cast<IColorable>(a)->GetColor() && Cast<IColorable>(b)->GetColor();
}

