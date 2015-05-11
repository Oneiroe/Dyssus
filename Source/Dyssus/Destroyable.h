// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Destroyable.generated.h"

UCLASS()
class DYSSUS_API ADestroyable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Destroy the object
	void Destroy();

	// Destroy with "collision" property the object  
	//virtual void Destroy(Collision_object collision) override;
	
	
};
