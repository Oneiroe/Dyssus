// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "DBarrier.h"


// Sets default values
ADBarrier::ADBarrier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collider->OnComponentBeginOverlap.AddDynamic(this, &ADBarrier::OnActorBeginOverlap);
}

// Called when the game starts or when spawned
void ADBarrier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADBarrier::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADBarrier::OnConstruction(const FTransform& Transform)
{
	// TODO Dynamically scale mesh
}

void ADBarrier::OnActorBeginOverlap(class AActor* OtherActor,
									class UPrimitiveComponent* OtherComp,
									int32 OtherBodyIndex,
									bool bFromSweep,
									const FHitResult &SweepResult)
{
	//TODO Handle different situations according to the design
}
