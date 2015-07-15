// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "DCharacter.h"
#include "DButton.h"


// Sets default values
ADButton::ADButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// The button has a box collider, which represents the volume for the overlap to press the button
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADButton::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ADButton::OnEndOverlap);
	SphereComponent->bGenerateOverlapEvents = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetActorEnableCollision(true);

	RootComponent = StaticMeshComponent;
	SphereComponent->AttachParent = StaticMeshComponent;

	// The button is not pressed by default
	SetPressed(false);

	numOverlappingActors = 0;
	deltaHeight = 20;
	interpSpeed = 100;
}

// Called when the game starts or when spawned
void ADButton::BeginPlay()
{
	Super::BeginPlay();

	initialZ = GetActorLocation().Z;
}

// Called every frame
void ADButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isPressed) PressButton(DeltaTime);
	else ReleaseButton(DeltaTime);
}

void ADButton::OnConstruction(const FTransform& Transform)
{
	SetPressed(isPressed);

	initialZ = GetActorLocation().Z;
}

void ADButton::OnBeginOverlap(class AActor* OtherActor,
class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ADCharacter::StaticClass()) || OtherActor->Implements<UGrabbableInterface>())
	{
		numOverlappingActors++;

		if (!isPressed)
		{
			SetPressed(true);

			if (onPressSound) PlaySoundAtLocation(onPressSound, GetActorLocation());
		}
	}
}

void ADButton::OnEndOverlap(class AActor * OtherActor,
class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ADCharacter::StaticClass()) || OtherActor->Implements<UGrabbableInterface>())
	{
		numOverlappingActors--;

		if (!numOverlappingActors)
		{
			SetPressed(false);

			if (onReleaseSound) PlaySoundAtLocation(onReleaseSound, GetActorLocation());

			// Needed for generating overlapping events
			SphereComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		}
	}
}

void ADButton::SetPressed(bool newPressed)
{
	isPressed = newPressed;
}

bool ADButton::IsButtonPressed()
{
	return isPressed;
}

USoundCue* ADButton::GetOnReleaseSound()
{
	return onReleaseSound;
}

void ADButton::SetOnReleaseSound(USoundCue* newReleaseSound)
{
	onReleaseSound = newReleaseSound;
}

USoundCue* ADButton::GetOnPressSound()
{
	return onPressSound;
}

void ADButton::SetOnPressSound(USoundCue* newPressSound)
{
	onPressSound = newPressSound;
}

void ADButton::PressButton(float DeltaTime)
{
	float z = FMath::FInterpTo(GetActorLocation().Z, initialZ - deltaHeight, DeltaTime, interpSpeed);
	FVector loc = GetActorLocation();
	loc.Z = z;

	SetActorLocation(loc);
}

void ADButton::ReleaseButton(float DeltaTime)
{
	float z = FMath::FInterpTo(GetActorLocation().Z, initialZ, DeltaTime, interpSpeed);
	FVector loc = GetActorLocation();
	loc.Z = z;

	SetActorLocation(loc);
}
