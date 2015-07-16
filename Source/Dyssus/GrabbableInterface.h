// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GrabbableInterface.generated.h"

/** Class needed to support InterfaceCast<IGrabbableInterface>(Object) */
UINTERFACE(MinimalAPI, Blueprintable) 
class UGrabbableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IGrabbableInterface
{
	GENERATED_IINTERFACE_BODY()
};