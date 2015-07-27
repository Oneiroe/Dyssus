// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DButton.generated.h"

UCLASS()
class DYSSUS_API ADButton : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADButton();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	/** Height of the button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float DeltaHeight;

	/** Button press/release speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float InterpSpeed;

	// Returns whether the button is currently pressed (true) or released (false)
	UFUNCTION(BlueprintCallable, Category = State)
	bool IsButtonPressed();

	/** Sets whether this button is pressed */
	UFUNCTION(BlueprintCallable, Category = State)
	void SetPressed(bool newPressed);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UStaticMeshComponent* StaticMeshComponent;

	// Setters and getters for release sound
	UFUNCTION(BlueprintCallable, Category = Sounds)
	USoundCue* GetOnReleaseSound();

	UFUNCTION(BlueprintCallable, Category = Sounds)
	void SetOnReleaseSound(USoundCue* releaseSound);

	// Setters and getters for press sound
	UFUNCTION(BlueprintCallable, Category = Sounds)
	USoundCue* GetOnPressSound();

	UFUNCTION(BlueprintCallable, Category = Sounds)
	void SetOnPressSound(USoundCue* pressSound);

	// Functions for collisions
	UFUNCTION(BlueprintCallable, Category = Collision)
	void OnBeginOverlap(class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex,
						bool bFromSweep,
						const FHitResult &SweepResult);

	UFUNCTION(BlueprintCallable, Category = Collision)
	void OnEndOverlap(class AActor * OtherActor,
					class UPrimitiveComponent* OtherComp,
					int32 OtherBodyIndex);

	// delegate to signal the button status change to associated objects
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonStatusChangeDelegate);
	
	// return the reference to the button status delegate object
	FButtonStatusChangeDelegate& OnButtonStatusChange() { return EventButtonStatusChange; }



private:

	// event thrown on button status change
	UPROPERTY(BlueprintAssignable)
	FButtonStatusChangeDelegate EventButtonStatusChange;

	int NumOverlappingActors;

	void PressButton(float DeltaTime);

	void ReleaseButton(float DeltaTime);

	float InitialZ;

	bool ReachedState;

	// This indicates whether the button is currently pressed (true) or released (false)
	UPROPERTY(EditAnywhere, Category = State)
	bool IsPressed;

	// Sound played when the button is released
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundCue* OnReleaseSound;

	// Sound played when the button is pressed
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundCue* OnPressSound;
};