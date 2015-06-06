// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "DestroyableInterface.generated.h"

/** Class needed to support InterfaceCast<IDestroyableInterface>(Object) */
UINTERFACE(MinimalAPI, Blueprintable) 
class UDestroyableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class IDestroyableInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	// TODO Possible redundancy
	// launch the destroy function of the destroyable object
	virtual void interfacedDestroy();
	virtual void interfacedDestroy(FVector HitLocation, FVector NormalImpulse);
};
