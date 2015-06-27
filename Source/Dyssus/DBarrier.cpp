// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "DBarrier.h"
#include "DCharacter.h"
#include "Cube.h"
#include "DStaticLibrary.h"


// Sets default values
ADBarrier::ADBarrier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Box Collider size should be adjust in Blueprint according to Static Mesh Component size
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADBarrier::OnBeginOverlap);
	BoxComponent->bGenerateOverlapEvents = true;

	// Mesh should be conveniently set in Blueprint
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetActorEnableCollision(true);

	RootComponent = StaticMeshComponent;
	BoxComponent->AttachParent = StaticMeshComponent;

	// Barrier is crossable by default
	SetCrossable(true);

	// White is the default color for barriers
	barrierColor = DTypes::DCOLOR::WHITE;
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
	SetCrossable(IsCrossable);
}

void ADBarrier::OnBeginOverlap(class AActor* OtherActor,
									class UPrimitiveComponent* OtherComp,
									int32 OtherBodyIndex,
									bool bFromSweep,
									const FHitResult &SweepResult)
{
	UDStaticLibrary::Print("Overlap event generated!");

	if (OtherActor->IsA(ADCharacter::StaticClass()))
	{
		UDStaticLibrary::Print("It's a pawn!");

		ADCharacter* character = Cast<ADCharacter>(OtherActor);
		UPrimitiveComponent* grabbedObj = character->grabbedObject;

		if (character->grabbedObject != NULL && character->cubeColor != DTypes::DCOLOR::NONE)
		{
			UDStaticLibrary::Print("It's a cube!");
			if (barrierColor != character->cubeColor)
			{
				UDStaticLibrary::Print("Should drop!");
				character->DropObject();
			}
		}
	}
	if (OtherActor->IsA(ACube::StaticClass()))
	{
		UDStaticLibrary::Print("Again a cube!");

		ACube* cube = Cast<ACube>(OtherActor);

		if (barrierColor == cube->getCurrentColor())
		{
			UDStaticLibrary::Print("Even same color!");
			BoxComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		}
		else BoxComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	}

	if (OverlapSound != NULL)
		UGameplayStatics::PlaySoundAtLocation(this, OverlapSound, GetActorLocation());
}

void ADBarrier::SetCrossable(bool newCrossable)
{
	if (newCrossable != IsCrossable)
	{
		if (newCrossable) BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		else BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	}

	IsCrossable = newCrossable;
}