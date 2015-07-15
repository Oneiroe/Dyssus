// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DStaticLibrary.h"
#include "Colorable.h"
#include "ColorableFactory.h"
#include "DBarrier.generated.h"

UCLASS(Blueprintable)
class DYSSUS_API ADBarrier : public AActor, public IColorable
{
	GENERATED_BODY()

	UColorableFactory* ColorableFactory;
	
public:
	ADBarrier();

	DTypes::DCOLOR DColor;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UBoxComponent* BoxComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    UMaterial* currentMaterial;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    bool canChangeColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TEnumAsByte<DTypes::DCOLOR> BarrierColor;

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool IsCrossable;

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void SetCrossable(bool newCrossable);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void OnBeginOverlap
	(
		class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult &SweepResult
	);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void OnEndOverlap
	(
		class AActor * OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
    
    // Edit the current color of the barrier
    UFUNCTION(BlueprintCallable, category = "Barrier")
    void setCurrentColor(UMaterial* newCurrentMaterial, DTypes::DCOLOR cColor);
};