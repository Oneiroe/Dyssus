// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DStaticLibrary.h"
#include "ColorableFactory.generated.h"

/**
 * 
 */
UCLASS()
class DYSSUS_API UColorableFactory : public UObject
{
public:
    GENERATED_BODY()
   
    static AActor* Instantiate(UWorld* World,
                               UClass* ClassToSpawn,
                               UMaterial* Material,
                               DTypes::DCOLOR Color);
	
};
