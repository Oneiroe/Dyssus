// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DStaticLibrary.h"
#include "ColorableFactory.generated.h"

/**
*
*/
UCLASS(Blueprintable)
class DYSSUS_API UColorableFactory : public UBlueprintFunctionLibrary
{

public:

	GENERATED_BODY()

	/** Compares the colors of the two actors */
	UFUNCTION(BlueprintCallable, Category = Colors)
	static bool CompareColors(AActor* a, AActor* b);
};
