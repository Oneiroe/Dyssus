// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DStaticLibrary.h"
#include "Colorable.h"
#include "DButton.h"
#include "DBarrier.generated.h"

UCLASS(Blueprintable)
class DYSSUS_API ADBarrier : public AActor, public IColorable
{
	GENERATED_BODY()

	UMaterial* CurrentMaterial;

public:
	ADBarrier();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	/** Returns the current color of the barrier */
	UFUNCTION(BlueprintCallable, Category = Colors)
	virtual DTypes::DCOLOR GetColor() override;

	/** Sets the color of the barrier */
	UFUNCTION(BlueprintCallable, Category = Colors)
	virtual void SetColor(DTypes::DCOLOR dColor) override;

	/** Current color of the barrier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	TEnumAsByte<DTypes::DCOLOR> DColor;

	/** Static mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UStaticMeshComponent* StaticMeshComponent;

	/** Box component for overlap events */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UBoxComponent* BoxComponent;

	/** Sounds to be used for barrier interactions */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* OverlapSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* OverlapDropObjSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* ChangeColorSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* ActivatedSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* DeactivatedSound;

	/** Whether this barrier is crossable */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool IsCrossable;

	/** Whether this barrier is active */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool IsActivated;

	/** Array of materials, one per each color */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	TArray<UMaterial*> BarrierMaterials;

	/** Set whether this barrier is crossable */
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void SetCrossable(bool newCrossable);

	/** OnBeginOverlap callback */
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void OnBeginOverlap(class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex,
						bool bFromSweep,
						const FHitResult &SweepResult);

	/** OnEndOverlap callback */
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void OnEndOverlap(class AActor * OtherActor,
					class UPrimitiveComponent* OtherComp,
					int32 OtherBodyIndex);	
	
	// Thrown when an input button has changed status
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBarrierBehaviorChangeDelegate);

private:
	// Thrown receiving an associated button status change signal
	UFUNCTION(BlueprintCallable, category = "Input Signal Handling")
	void OnInputChange();

	// event thrown when an input button has changed status
	UPROPERTY(BlueprintAssignable)
	FBarrierBehaviorChangeDelegate EventBehaviorChange;

	// Buttons of which input will be handled
	UPROPERTY(EditAnywhere, category = "Input Signal Handling")
	TArray<ADButton*> InputButtonsActors;


};
