// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DStaticLibrary.h"
#include "DBarrier.generated.h"

UCLASS()
class DYSSUS_API ADBarrier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADBarrier();

	// ADBarrier(const FObjectInitializer& ObjectInitializer);

	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UBoxComponent* collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* overlapSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* overlapDropObjSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* changeColorSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* activatedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* deactivatedSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool isCrossable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UMaterial* material;

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void OnActorBeginOverlap
	(
		class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult &SweepResult
	);
};
