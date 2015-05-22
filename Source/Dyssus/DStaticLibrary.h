// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DStaticLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DYSSUS_API UDStaticLibrary : public UObject
{
public:
	GENERATED_UCLASS_BODY()

protected:
	static FORCEINLINE bool Trace(
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		FHitResult& HitOut,
		ECollisionChannel CollisionChannel = ECC_Pawn,
		bool ReturnPhysMat = false
		);
};
