// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "DBarrier.h"
#include "DCharacter.h"
#include "Cube.h"
#include "DStaticLibrary.h"
#include "ColorableFactory.h"


// Sets default values
ADBarrier::ADBarrier()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Box Collider size should be adjust in Blueprint according to Static Mesh Component size
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADBarrier::OnBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ADBarrier::OnEndOverlap);
	BoxComponent->bGenerateOverlapEvents = true;

	// Mesh should be conveniently set in Blueprint
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetActorEnableCollision(true);

	RootComponent = StaticMeshComponent;
	BoxComponent->AttachParent = StaticMeshComponent;

	// Barrier is crossable by default
	SetCrossable(true);
}

// Called when the game starts or when spawned
void ADBarrier::BeginPlay()
{
	Super::BeginPlay();

	for (ADButton* i : InputButtonsActors)
	{
		i->OnButtonStatusChange().AddDynamic(this, &ADBarrier::OnInputChange); //  handshacking between the object and its buttons
	}
}

// Thrown when an associated button changes state
void ADBarrier::OnInputChange()
{
	EventBehaviorChange.Broadcast(); //  signal to the game that the object inputs are changed and the object itself has to re-check its status(doing it via levelblueprint)
}

// Called every frame
void ADBarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Reset Collision Profile Name to "Barrier_OverlapAll" in order to generate overlap events -- possible performance bug
	if (IsCrossable && BoxComponent->GetCollisionProfileName() != "Barrier_OverlapAll")
	{
		TArray<AActor*> overlappingActors;
		BoxComponent->GetOverlappingActors(overlappingActors);
		if (overlappingActors.Num() == 0) BoxComponent->SetCollisionProfileName("Barrier_OverlapAll");
	}
}

void ADBarrier::OnConstruction(const FTransform& Transform)
{
	SetCrossable(IsCrossable);

	SetColor(DColor);
}

void ADBarrier::OnBeginOverlap(class AActor* OtherActor,
class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	if (!IsActivated) return;

	if (OtherActor->IsA(ADCharacter::StaticClass()))
	{
		ADCharacter* character = Cast<ADCharacter>(OtherActor);
		UPrimitiveComponent* grabbedObj = (UPrimitiveComponent*)character->GrabbedObject;

		if (character->GrabbedObject && UColorableFactory::CompareColors(this, Cast<AActor>(grabbedObj)))
			character->DropObject();
	}
	if (OtherActor->IsA(ACube::StaticClass()))
	{
		ACube* cube = Cast<ACube>(OtherActor);

		if (UColorableFactory::CompareColors(this, cube))
			BoxComponent->SetCollisionProfileName("Barrier_OverlapAll");
		else
			BoxComponent->SetCollisionProfileName("Barrier_BlockCube");
	}

	if (OverlapSound) UGameplayStatics::PlaySoundAtLocation(this, OverlapSound, GetActorLocation());
}

void ADBarrier::OnEndOverlap(class AActor * OtherActor,
							class UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex)
{
	// Remaining overlapping actors check should go here, but it caused a stack overflow
}

// Whenever IsCrossable is changed, Pawn channel response changes too
void ADBarrier::SetCrossable(bool newCrossable)
{
	if (newCrossable) BoxComponent->SetCollisionProfileName("Barrier_OverlapAll");
	else BoxComponent->SetCollisionProfileName("BlockAll");

	IsCrossable = newCrossable;
}

void ADBarrier::SetColor(DTypes::DCOLOR dColor)
{
	DColor = dColor;

	if (BarrierMaterials.Num() > DColor)
	{
		CurrentMaterial = BarrierMaterials[dColor];
		StaticMeshComponent->SetMaterial(0, CurrentMaterial);
	}
}

DTypes::DCOLOR ADBarrier::GetColor()
{
	return DColor;
}