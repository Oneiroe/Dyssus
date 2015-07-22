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

	NumOverlappingActors = 0;
	DeltaHeight = 20;
	InterpSpeed = 100;
}

// Called when the game starts or when spawned
void ADButton::BeginPlay()
{
	Super::BeginPlay();

	InitialZ = GetActorLocation().Z;
}

// Called every frame
void ADButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsPressed) PressButton(DeltaTime);
	else ReleaseButton(DeltaTime);
}

void ADButton::OnConstruction(const FTransform& Transform)
{
	SetPressed(IsPressed);

	InitialZ = GetActorLocation().Z;
}

void ADButton::OnBeginOverlap(class AActor* OtherActor,
class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ADCharacter::StaticClass()) || OtherActor->Implements<UGrabbableInterface>())
	{
		NumOverlappingActors++;

		if (!IsPressed)
		{
			SetPressed(true);

			if (OnPressSound) PlaySoundAtLocation(OnPressSound, GetActorLocation());
		}
	}
}

void ADButton::OnEndOverlap(class AActor * OtherActor,
class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ADCharacter::StaticClass()) || OtherActor->Implements<UGrabbableInterface>())
	{
		NumOverlappingActors--;

		if (!NumOverlappingActors)
		{
			SetPressed(false);

			if (OnReleaseSound) PlaySoundAtLocation(OnReleaseSound, GetActorLocation());

		}
	}
}

void ADButton::SetPressed(bool newPressed)
{
	IsPressed = newPressed;

	if (IsPressed) OnButtonPressed();
	else OnButtonReleased();
}

bool ADButton::IsButtonPressed()
{
	return IsPressed;
}

USoundCue* ADButton::GetOnReleaseSound()
{
	return OnReleaseSound;
}

void ADButton::SetOnReleaseSound(USoundCue* newReleaseSound)
{
	OnReleaseSound = newReleaseSound;
}

USoundCue* ADButton::GetOnPressSound()
{
	return OnPressSound;
}

void ADButton::SetOnPressSound(USoundCue* newPressSound)
{
	OnPressSound = newPressSound;
}

void ADButton::PressButton(float DeltaTime)
{
	float z = FMath::FInterpTo(GetActorLocation().Z, InitialZ - DeltaHeight, DeltaTime, InterpSpeed);
	FVector loc = GetActorLocation();
	loc.Z = z;

	SetActorLocation(loc);
}

void ADButton::ReleaseButton(float DeltaTime)
{
	float z = FMath::FInterpTo(GetActorLocation().Z, InitialZ, DeltaTime, InterpSpeed);
	FVector loc = GetActorLocation();
	loc.Z = z;

	SetActorLocation(loc);
}
