// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "CubeColorator.h"

ACubeColorator::ACubeColorator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACubeColorator::OnConstruction(const FTransform& Transform)
{

}

// Called when the game starts or when spawned
void ACubeColorator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACubeColorator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Returns the color Material of the colorator
TEnumAsByte<DTypes::DCOLOR> ACubeColorator::GetColor()
{
	return ColoratorColor;
}

// Changes the color used by the colorator
void ACubeColorator::SetColor(DTypes::DCOLOR newColor)
{
	ColoratorColor = newColor;
	if (SoundChangeColor) UGameplayStatics::PlaySoundAtLocation(this, SoundChangeColor, GetActorLocation());
}

// Returns whether the colorator is active or not
bool ACubeColorator::GetActiveStatus()
{
	return IsActive;
}

// Set the colorator to active or not
void ACubeColorator::SetActiveStatus(bool newBehaviour)
{
	IsActive = newBehaviour;
	if (newBehaviour==true && SoundStartUp) UGameplayStatics::PlaySoundAtLocation(this, SoundStartUp, GetActorLocation());
	else if (SoundShoutdown) UGameplayStatics::PlaySoundAtLocation(this, SoundShoutdown, GetActorLocation());
}

void ACubeColorator::ReceiveActorBeginOverlap(AActor * OtherActor)
{
	if (!IsActive) return;
	
	if (OtherActor && OtherActor != this)
	{
		ACube* cubeCollided = Cast<ACube>(OtherActor);
		if (!cubeCollided) return;

		cubeCollided->SetColor(ColoratorColor);
		if (SoundUsed) UGameplayStatics::PlaySoundAtLocation(this, SoundUsed, GetActorLocation());
	}
}