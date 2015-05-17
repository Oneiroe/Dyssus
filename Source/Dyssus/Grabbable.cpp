// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "Grabbable.h"


// Sets default values
AGrabbable::AGrabbable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrabbable::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGrabbable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// The signature of this method has been added to resolve a build error, but its body has yet to be implemented
void AGrabbable::Grab(){}