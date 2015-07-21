// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "DGate.h"


// Sets default values
ADGate::ADGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent1"));
	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent2"));

	SetRootComponent(BoxTrigger);
	Mesh1->AttachTo(RootComponent);
	Mesh2->AttachTo(RootComponent);

	SetState(true);

	InterpSpeed = 100.f;
}

// Called when the game starts or when spawned
void ADGate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADGate::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (IsOpen) OpenGate(DeltaTime);
	else CloseGate(DeltaTime);
}

void ADGate::SetState(bool newState, bool snap)
{
	IsOpen = newState;

	if (snap)
	{
		if (newState)
		{
			Mesh1->SetRelativeLocation(Mesh1OpenOffset);
			Mesh2->SetRelativeLocation(Mesh2OpenOffset);
		}
		else
		{
			Mesh1->SetRelativeLocation(Mesh1CloseOffset);
			Mesh2->SetRelativeLocation(Mesh2CloseOffset);
		}
	}
}

void ADGate::OpenGate(float DeltaTime)
{
	FVector mesh1RL = Mesh1->GetRelativeTransform().GetLocation();
	FVector mesh2RL = Mesh1->GetRelativeTransform().GetLocation();

	float offset1X = FMath::FInterpTo(mesh1RL.X, Mesh1OpenOffset.X, DeltaTime, InterpSpeed);
	float offset1Y = FMath::FInterpTo(mesh1RL.Y, Mesh1OpenOffset.Y, DeltaTime, InterpSpeed);
	float offset1Z = FMath::FInterpTo(mesh1RL.Z, Mesh1OpenOffset.Z, DeltaTime, InterpSpeed);

	FVector mesh1NewRL = FVector(offset1X, offset1Y, offset1Z);

	Mesh1->SetRelativeLocation(mesh1NewRL);

	float offset2X = FMath::FInterpTo(mesh2RL.X, Mesh2OpenOffset.X, DeltaTime, InterpSpeed);
	float offset2Y = FMath::FInterpTo(mesh2RL.Y, Mesh2OpenOffset.Y, DeltaTime, InterpSpeed);
	float offset2Z = FMath::FInterpTo(mesh2RL.Z, Mesh2OpenOffset.Z, DeltaTime, InterpSpeed);

	FVector mesh2NewRL = FVector(offset2X, offset2Y, offset2Z);

	Mesh2->SetRelativeLocation(mesh2NewRL);
}

void ADGate::CloseGate(float DeltaTime)
{
	FVector mesh1RL = Mesh1->GetRelativeTransform().GetLocation();
	FVector mesh2RL = Mesh1->GetRelativeTransform().GetLocation();

	float offset1X = FMath::FInterpTo(mesh1RL.X, Mesh1CloseOffset.X, DeltaTime, InterpSpeed);
	float offset1Y = FMath::FInterpTo(mesh1RL.Y, Mesh1CloseOffset.Y, DeltaTime, InterpSpeed);
	float offset1Z = FMath::FInterpTo(mesh1RL.Z, Mesh1CloseOffset.Z, DeltaTime, InterpSpeed);

	FVector mesh1NewRL = FVector(offset1X, offset1Y, offset1Z);

	Mesh1->SetRelativeLocation(mesh1NewRL);

	float offset2X = FMath::FInterpTo(mesh2RL.X, Mesh2CloseOffset.X, DeltaTime, InterpSpeed);
	float offset2Y = FMath::FInterpTo(mesh2RL.Y, Mesh2CloseOffset.Y, DeltaTime, InterpSpeed);
	float offset2Z = FMath::FInterpTo(mesh2RL.Z, Mesh2CloseOffset.Z, DeltaTime, InterpSpeed);

	FVector mesh2NewRL = FVector(offset2X, offset2Y, offset2Z);

	Mesh2->SetRelativeLocation(mesh2NewRL);
}
