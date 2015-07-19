// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "ColorableFactory.h"
#include "DStaticLibrary.h"
#include "Colorable.h"
#include "Cube.h"
#include "DBarrier.h"

bool UColorableFactory::CompareColors(AActor* a, AActor* b)
{
	IColorable* aa = InterfaceCast<IColorable>(a);
	IColorable* bb = InterfaceCast<IColorable>(b);

	if (!aa || !bb) return false;

	return aa->GetColor() == bb->GetColor();
}

