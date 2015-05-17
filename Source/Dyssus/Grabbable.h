// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Grabbable.generated.h"

UCLASS()
class DYSSUS_API AGrabbable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGrabbable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Make the object be grabbed by the character 
	virtual void Grab();
};