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

	// White is the default color for barriers
	BarrierColor = DTypes::DCOLOR::WHITE;

	ColorableFactory = CreateDefaultSubobject<UColorableFactory>(TEXT("ColorableFactory"));
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

	ColorableFactory->GetMaterialFromColorAndClass(this->GetClass(), currentMaterial, DColor);
	StaticMeshComponent->SetMaterial(0, currentMaterial);
}

void ADBarrier::OnBeginOverlap(class AActor* OtherActor,
								class UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex,
								bool bFromSweep,
								const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ADCharacter::StaticClass()))
	{
		ADCharacter* character = Cast<ADCharacter>(OtherActor);
		UPrimitiveComponent* grabbedObj = character->grabbedObject;

		// Weakly check if the character is carrying a cube
		if (character->grabbedObject != NULL && character->cubeColor != DTypes::DCOLOR::NONE)
		{
			// If cube color and barrier color are different cube should be dropped
			if (BarrierColor != character->cubeColor)
				character->DropObject();
		}
	}
	if (OtherActor->IsA(ACube::StaticClass()))
	{
		ACube* cube = Cast<ACube>(OtherActor);

		// Setting collision to 'Collision Enabled' stops cube but not character
		if (ColorableFactory->CompareColors(this, cube))
			BoxComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		else BoxComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	}

	if (OverlapSound != NULL)
		UGameplayStatics::PlaySoundAtLocation(this, OverlapSound, GetActorLocation());
}

void ADBarrier::OnEndOverlap(class AActor * OtherActor,
							class UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex)
{
	// Needed for generating overlapping events
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
}

// Whenever IsCrossable is changed, Pawn channel response changes too
void ADBarrier::SetCrossable(bool newCrossable)
{
	if (newCrossable != IsCrossable)
	{
		if (newCrossable) BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		else BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	}

	IsCrossable = newCrossable;
}

void ADBarrier::setCurrentColor(UMaterial* newCurrentMaterial, DTypes::DCOLOR color)
{
    UE_LOG(LogTemp, Warning, TEXT("ADBarrier->setCurrentColor()"));
    if (canChangeColor == false) return;
    //print("ACube->setCurrentColor()");
    //this->GetDestructibleComponent()->SetMaterial(0, newCurrentColor);
    TArray<UStaticMeshComponent*> Components;
    this->GetComponents<UStaticMeshComponent>(Components);
    if (Components.Num() > 0)
        Components[0]->SetMaterial(0, newCurrentMaterial);
    currentMaterial = newCurrentMaterial;
    
    BarrierColor = color;
}

void ADBarrier::SetColor(DTypes::DCOLOR dColor)
{
	DColor = dColor;
	ColorableFactory->GetMaterialFromColorAndClass(this->GetClass(), currentMaterial, dColor);
}

DTypes::DCOLOR ADBarrier::GetColor()
{
	return DColor;
}