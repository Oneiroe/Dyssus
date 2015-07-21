// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DGate.generated.h"

UCLASS()
class DYSSUS_API ADGate : public AActor
{
	GENERATED_BODY()

	float offsetOpen;
	float offsetClose;
	
public:

	// Sets default values for this actor's properties
	ADGate();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	class UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	class UStaticMeshComponent* Mesh1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	class UStaticMeshComponent* Mesh2;

	UFUNCTION(BlueprintCallable, Category = State)
	void SetState(bool newState, bool snap = false);

	UFUNCTION(BlueprintCallable, Category = State)
	void OpenGate(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = State)
	void CloseGate(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool IsOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector Mesh1OpenOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector Mesh1CloseOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector Mesh2OpenOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector Mesh2CloseOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float InterpSpeed;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool OpenOnProximity;
};