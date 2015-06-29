// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "DButton.h"


// Sets default values
ADButton::ADButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    // The button has a box collider, which represents the volume for the overlap to press the button
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADButton::OnBeginOverlap);
    BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ADButton::OnEndOverlap);
    BoxComponent->bGenerateOverlapEvents = true;
    
    StaticMeshcomponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    SetActorEnableCollision(true);
    
    RootComponent = StaticMeshComponent;
    BoxComponent->AttachParent = StaticMeshComponent;
    
    // The button is not pressed by default
    SetPressed(false);
}

// Called when the game starts or when spawned
void ADButton::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADButton::OnConstruction(const FTransform& Transform)
{
    SetPressed(isPressed);
}

void ADButton::OnBeginOverlap(class AActor* OtherActor,
                              class UPrimitiveComponent* OtherComp,
                              int32 OtherBodyIndex,
                              bool bFromSweep,
                              const FHitResult& SweepResult)
{
    // TODO:
    // If OtherActor is a DCharacter or a DCube, the button changes state to pressed (isPressed = true)
    // Play OnPressSound
}

void ADBarrier::OnEndOverlap(class AActor * OtherActor,
                             class UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex)
{
    // TODO:
    // Change the state to released (isPressed = false)
    // Play OnReleaseSound
    
    // Needed for generating overlapping events
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
}

