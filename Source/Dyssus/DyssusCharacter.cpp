// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "DyssusCharacter.h"


// Sets default values
ADyssusCharacter::ADyssusCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADyssusCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADyssusCharacter::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ADyssusCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

