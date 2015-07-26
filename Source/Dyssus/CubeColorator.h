// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Cube.h"
#include "DStaticLibrary.h"
#include "DButton.h"
#include "CubeColorator.generated.h"

UCLASS()
class DYSSUS_API ACubeColorator : public AActor
{
	GENERATED_BODY()

public:	

	// Sets default values for this actor's properties
	ACubeColorator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//UFUNCTION(BlueprintImplementableEvent, Meta = (FriendlyName = "ActorBeginOverlap"), Category = "Collision")
	// Called when this actor overlaps another actor
	virtual void ReceiveActorBeginOverlap(AActor* OtherActor) override;

	// To apply editor changes at realtime
	virtual void OnConstruction(const FTransform& Transform) override;

	// Returns the color Material of the colorator
	UFUNCTION(BlueprintCallable, category = "Colorator")
	TEnumAsByte<DTypes::DCOLOR> GetColor();

	// Change the color used by the colorator
	UFUNCTION(BlueprintCallable, category = "Colorator")
	void SetColor(DTypes::DCOLOR newColor);

	// Returns whether the colorator is active or not
	UFUNCTION(BlueprintCallable, category = "Colorator")
	bool GetActiveStatus();

	// Set the colorator to active or not
	UFUNCTION(BlueprintCallable, category = "Colorator")
	void SetActiveStatus(bool newBehaviour);	

	// Thrown when an input button has changed status
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FColoratorBehaviorChangeDelegate);


private:
	// Thrown receiving an associated button status change signal
	UFUNCTION(BlueprintCallable, category = "Input Signal Handling")
	void OnInputChange();

	// event thrown when an input button has changed status
	UPROPERTY(BlueprintAssignable)
	FColoratorBehaviorChangeDelegate EventBehaviorChange;
	
	// Buttons of which input will be handled
	UPROPERTY(EditAnywhere, category = "Input Signal Handling")
	TArray<ADButton*> InputButtonsActors;


	// Define if the colorator is active of not
	UPROPERTY(EditAnywhere)
	bool IsActive;

	// Material that define the color used to color the cube
	UPROPERTY(EditAnywhere)
	TEnumAsByte<DTypes::DCOLOR> ColoratorColor;

	// Sound played on colorator activation
	UPROPERTY(EditAnywhere)
	class USoundBase * SoundStartUp;

	// Sound played on colorator deactivation
	UPROPERTY(EditAnywhere)
	class USoundBase * SoundShoutdown;

	// Sound played changing color
	UPROPERTY(EditAnywhere)
	class USoundBase * SoundChangeColor;

	// Sound played on colorator utilization
	UPROPERTY(EditAnywhere)
	class USoundBase * SoundUsed;

};
