// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "DStaticLibrary.h"

UDStaticLibrary::UDStaticLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UDStaticLibrary::Trace(
	AActor* ActorToIgnore,
	const FVector& Start,
	const FVector& End,
	FHitResult& HitOut,
	ECollisionChannel CollisionChannel,
	bool ReturnPhysMat
	)
{
	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
	TraceParams.bTraceComplex = true;
	//TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	//Ignore Actors
	TraceParams.AddIgnoredActor(ActorToIgnore);

	//Re-initialize hit info
	HitOut = FHitResult(ForceInit);

	//Get World Context
	TObjectIterator< APlayerController > ThePC;
	if (!ThePC) return false;

	//Trace!
	ThePC->GetWorld()->LineTraceSingle(
		HitOut,		//result
		Start,	//start
		End, //end
		CollisionChannel, //collision channel
		TraceParams
		);

	//Hit any Actor?
	return (HitOut.GetActor() != NULL);
}

void UDStaticLibrary::Print(FString Message, FColor TextColor){
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, TextColor, Message);
}
