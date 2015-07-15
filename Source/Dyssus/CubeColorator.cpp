// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "CubeColorator.h"

// Sets default values
ACubeColorator::ACubeColorator()
{
	UE_LOG(LogTemp, Warning, TEXT("ACubeColorator->Constructor"));
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//let graphical part to blueprint extension
	//UBoxComponent* trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("triggerBox"));
	//UStaticMeshComponent* base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("base"));
	//base->AttachTo(trigger);
	//SetRootComponent(trigger);
}

// let graphical part to blueprint extension
void ACubeColorator::OnConstruction(const FTransform& Transform)
{
	UE_LOG(LogTemp, Warning, TEXT("ACubeColorator->OnConstruction()"));
	int inputNumbers = inputActors.Num();
	if (inputToHandle.Num() > pow(2.0, inputNumbers)) inputToHandle.SetNum(pow(2.0, inputNumbers));
	for (int i = 0; i < inputToHandle.Num(); i++)
	{
		inputToHandle[i].buttonsStatus.SetNum(inputNumbers, true);

		switch (inputToHandle[i].actionToPerform.GetValue())
		{
		case(CHANGE_COLOR) :
			UE_LOG(LogTemp, Warning, TEXT("ACubeColorator->OnConstruction()->CHANGE_COLOR selected"));
			
			//if the input is active or not
			UPROPERTY(EditAnywhere)
			inputToHandle[i].color;
			
			UPROPERTY(VisibleAnywhere)
			inputToHandle[i].switcher;
			break;
		case(SWITCH_ON) :
			UE_LOG(LogTemp, Warning, TEXT("ACubeColorator->OnConstruction()->SWITCH_ON selected"));

			//if the input is active or not
			UPROPERTY(VisibleAnywhere)
			inputToHandle[i].color;

			UPROPERTY(EditAnywhere)
			inputToHandle[i].switcher=true;
			break;
			
		case(SWITCH_OFF) :
						UE_LOG(LogTemp, Warning, TEXT("ACubeColorator->OnConstruction()->SWITCH_OFF selected"));

			//if the input is active or not
			UPROPERTY(VisibleAnywhere)
				inputToHandle[i].color;

			UPROPERTY(EditAnywhere)
				inputToHandle[i].switcher=false;
			break;
		default:
			break;
		}
	}
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
UMaterial* ACubeColorator::getColor()
{
	UE_LOG(LogTemp, Warning, TEXT("ACubeColorator->getColor"));
	return coloratorColor;
}

// Change the color used by the colorator
void ACubeColorator::setColor(UMaterial* newColor)
{
	UE_LOG(LogTemp, Warning, TEXT("ACubeColorator->setColor"));
	coloratorColor = newColor;
	if (soundChangeColor!=NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, soundChangeColor, GetActorLocation());
	}
}

// return if the colorator is active or not
bool ACubeColorator::getActiveStatus()
{
	UE_LOG(LogTemp, Warning, TEXT("ACubeColorator->getActiveStatus"));
	return isActive;
}

// set the colorator to active or not
void ACubeColorator::setActiveStatus(bool newBehaviour)
{
	UE_LOG(LogTemp, Warning, TEXT("ACubeColorator->setActiveStatus"));
	isActive = newBehaviour;
	if (newBehaviour==true)
	{
		if (soundStartUp!=NULL) UGameplayStatics::PlaySoundAtLocation(this, soundStartUp, GetActorLocation());
	}
	else
	{
		if (soundShoutdown!=NULL) UGameplayStatics::PlaySoundAtLocation(this, soundShoutdown, GetActorLocation());
	}
}

void ACubeColorator::NotifyActorBeginOverlap(AActor * OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("ACubeColorator->BeginOverlap"));
	if (isActive == false) return;
	
	if ((OtherActor != NULL) && (OtherActor != this))
	{
		ACube* cubeCollided = Cast<ACube>(OtherActor);
		if (cubeCollided == NULL) return;
		UE_LOG(LogTemp, Warning, TEXT("ACubeColorator->BeginOverlap->collidedACube"));
		cubeCollided->setCurrentColor(coloratorColor, DTypes::DCOLOR::WHITE);
		if (soundUsed != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, soundUsed, GetActorLocation());
		}
	}
}

/*template<class T> void ACubeColorator::inputHandling(TArray<T> inputs)
{
	UE_LOG(LogTemp, Warning, TEXT("ACubeColorator->inputHandling"));

}*/