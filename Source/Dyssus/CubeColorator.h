// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Cube.h"
#include "CubeColorator.generated.h"

UENUM()
enum inputHandlingBehaviour{
		LOGIC_AND                UMETA(DisplayName = "AND"),
		LOGIC_OR                    UMETA(DisplayName = "OR"),
		CUSTOM_LOGIC                    UMETA(DisplayName = "Custom")
};

UENUM()
enum inputCorrespondingAction{
	CHANGE_COLOR	UMETA(DisplayName = "Change Color"),
	SWITCH_ON		UMETA(DisplayName = "Switch ON"),
	SWITCH_OFF		UMETA(DisplayName = "Switch OFF")
};

USTRUCT()
struct FInput
{
	GENERATED_USTRUCT_BODY();

	//combination of input
	UPROPERTY(EditAnywhere)
	TArray<bool> buttonsStatus;

	//how to combine the inputs received
	UPROPERTY(EditAnywhere)
	TEnumAsByte<inputHandlingBehaviour> handlingBehaviour;

	//how to combine the inputs received
	UPROPERTY(EditAnywhere)
	TEnumAsByte<inputCorrespondingAction> actionToPerform;

	//if the input is active or not
	UPROPERTY(EditAnywhere)
	UMaterial* color;

	//if the input is active or not
	UPROPERTY(EditAnywhere)
	bool switcher;
};



UCLASS()
class DYSSUS_API ACubeColorator : public AActor
{
	GENERATED_BODY()

private:
	

	// define if the colorator is active of not
	UPROPERTY(EditAnywhere)
	bool isActive;

	// material that define the color used to color the cube
	UPROPERTY(EditAnywhere)
	UMaterial* coloratorColor;

	// sound played on colorator activation
	UPROPERTY(EditAnywhere)
	class USoundBase * soundStartUp;

	// sound played on colorator deactivation
	UPROPERTY(EditAnywhere)
	class USoundBase * soundShoutdown;

	// sound played changing color
	UPROPERTY(EditAnywhere)
	class USoundBase * soundChangeColor;

	// sound played on colorator utilization
	UPROPERTY(EditAnywhere)
	class USoundBase * soundUsed;

	// actor of which input will be handled
	UPROPERTY(EditAnywhere)
	TArray<AActor*> inputActors;

	// input to handle
	UPROPERTY(EditAnywhere)
	TArray<FInput> inputToHandle;



public:	


	// Sets default values for this actor's properties
	ACubeColorator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//UFUNCTION(BlueprintImplementableEvent, Meta = (FriendlyName = "ActorBeginOverlap"), Category = "Collision")
	// Called when this actor overlaps another actor
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// To apply editor changes at realtime
	virtual void OnConstruction(const FTransform& Transform) override;


	// Returns the color Material of the colorator
	UFUNCTION(BlueprintCallable, category = "Colorator")
	UMaterial* getColor();

	// Change the color used by the colorator
	UFUNCTION(BlueprintCallable, category = "Colorator")
	void setColor(UMaterial* newColor);

	// return if the colorator is active or not
	UFUNCTION(BlueprintCallable, category = "Colorator")
	bool getActiveStatus();

	// set the colorator to active or not
	UFUNCTION(BlueprintCallable, category = "Colorator")
	void setActiveStatus(bool newBehaviour);	
	
	//UFUNCTION(BlueprintCallable, category = "Colorator")
	//template<class T> void inputHandling(TArray<T> inputs);
};
