// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "DCharacter.h"
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
	Mesh1->SetRelativeRotation(FRotator(0, 0, 90));
	
	Mesh2->AttachTo(RootComponent);
	Mesh2->SetRelativeRotation(FRotator(0, 0, -90));

	SetState(false);

	InterpSpeed = 100.f;

	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADGate::OnBeginOverlap);
	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &ADGate::OnEndOverlap);

	OpenOnProximity = true;
}

// Called when the game starts or when spawned
void ADGate::BeginPlay()
{
	Super::BeginPlay();
	
	for (ADButton* i : InputButtonsActors)
	{
		i->OnButtonStatusChange().AddDynamic(this, &ADGate::OnInputChange); //  handshacking between the colorator and its buttons
	}
}

// Thrown when an associated button changes state
void ADGate::OnInputChange()
{
	EventBehaviorChange.Broadcast(); //  signal to the game that the object inputs are changed and the object itself has to re-check 
}

// Called every frame
void ADGate::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (IsOpen) OpenGate(DeltaTime);
	else CloseGate(DeltaTime);
}

void ADGate::OnConstruction(const FTransform& Transform)
{
	SetState(IsOpen, true);
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
	FVector mesh2RL = Mesh2->GetRelativeTransform().GetLocation();

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
	FVector mesh2RL = Mesh2->GetRelativeTransform().GetLocation();

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

void ADGate::OnBeginOverlap(class AActor* OtherActor,
							class UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex,
							bool bFromSweep,
							const FHitResult &SweepResult)
{
	if (!OpenOnProximity) return;

	if (OtherActor->IsA(ADCharacter::StaticClass()))
	{
		SetState(true);
	}
}

void ADGate::OnEndOverlap(class AActor * OtherActor,
						class UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex)
{
	if (!OpenOnProximity) return;

	if (OtherActor->IsA(ADCharacter::StaticClass()))
	{
		SetState(false);
	}
}