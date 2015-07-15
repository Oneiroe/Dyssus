// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DButton.generated.h"

UCLASS()
class DYSSUS_API ADButton : public AActor
{
	GENERATED_BODY()

private:
	int numOverlappingActors;

	void PressButton(float DeltaTime);

	void ReleaseButton(float DeltaTime);

	float initialZ;

	// This indicates whether the button is currently pressed (true) or released (false)
	UPROPERTY(EditAnywhere, Category = State)
		bool isPressed;

	// Sound played when the button is released
	UPROPERTY(EditAnywhere, Category = Sounds)
		USoundCue* onReleaseSound;

	// Sound played when the button is pressed
	UPROPERTY(EditAnywhere, Category = Sounds)
		USoundCue* onPressSound;

public:
	// Sets default values for this actor's properties
	ADButton();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float deltaHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float interpSpeed;

	// Returns whether the button is currently pressed (true) or released (false)
	UFUNCTION(BlueprintCallable, Category = State)
		bool IsButtonPressed();

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
};