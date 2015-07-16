// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DestroyableInterface.h"
#include "GrabbableInterface.h"
#include "Colorable.h"
#include "DStaticLibrary.h"
#include "Cube.generated.h"

UCLASS(Blueprintable)
class DYSSUS_API ACube : public AActor, public IDestroyableInterface, public IGrabbableInterface, public IColorable
{
	GENERATED_BODY()

private:

	UMaterial* Material;

	UPROPERTY(EditAnywhere)
	bool CanChangeColor;

	// Initial location of the cube on level start
	UPROPERTY(VisibleAnywhere)
	FVector StartingLocation;

	// Location that the cube will reach on respawn
	UPROPERTY(EditAnywhere)
	FVector RespawnLocation;

	UPROPERTY(EditAnywhere)
	bool Respawnable;

	// Default color on respawn?
	UPROPERTY(EditAnywhere)
	bool MaintainColorOnRespawn;

	UPROPERTY(EditAnywhere)
	bool CanBeDestroyed;

	// Define if the cube will be respawned at his starting location or at the respawn one
	UPROPERTY(EditAnywhere)
	bool UseStartingLocationOnRespawn;

	// Respawns the cube with the property set on construction
	void RespawnCube();

public:

	class UStaticMeshComponent* StaticMesh;

	class UDestructibleComponent* DestructibleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rendering)
	class UStaticMesh* SMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rendering)
	class UDestructibleMesh* DMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	TEnumAsByte<DTypes::DCOLOR> DDefaultColor;

	UFUNCTION(BlueprintCallable, Category = Colors)
	TEnumAsByte<DTypes::DCOLOR> GetDefaultColor();

	UFUNCTION(BlueprintCallable, Category = Colors)
	void SetDefaultColor(DTypes::DCOLOR defColor_);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	TEnumAsByte<DTypes::DCOLOR> DColor;

	UFUNCTION(BlueprintCallable, Category = Colors)
	virtual DTypes::DCOLOR GetColor() override;

	UFUNCTION(BlueprintCallable, Category = Colors)
	virtual void SetColor(DTypes::DCOLOR dColor_) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	TArray<UMaterial*> CubeMaterials;

	UObject* CubeMesh;

	// Sets default values for this actor's properties
	ACube();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Returns if the cube can change color or is a permanent one
	UFUNCTION(BlueprintCallable, category = "Cube")
	bool GetCanChangeColor();

	// Make the cube color changing possible or not
	UFUNCTION(BlueprintCallable, category = "Cube")
	void SetCanChangeColor(bool changeBehaviour);

	// Return the starting location of the cube
	UFUNCTION(BlueprintCallable, category = "Cube")
	FVector GetStartingLocation();

	// Edit the starting location of the cube
	UFUNCTION(BlueprintCallable, category = "Cube")
	void SetStartingLocation(FVector newStartingLocation);//REMOVE-PENDING

	// Return the respawn location
	UFUNCTION(BlueprintCallable, category = "Cube")
	FVector GetRespawnLocation();

	// Edit the respawn location
	UFUNCTION(BlueprintCallable, category = "Cube")
	void SetRespawnLocation(FVector new_location);

	// Returns if the cube can be respawned or not
	UFUNCTION(BlueprintCallable, category = "Cube")
	bool GetRespawnable();

	// Edit if the cube can be respawned or not
	UFUNCTION(BlueprintCallable, category = "Cube")
	void SetRespawnable(bool changeBehaviour);

	// Returns if the cube change color on the respawn or not
	UFUNCTION(BlueprintCallable, category = "Cube")
	bool GetMaintainColorOnRespawn();

	// Edit if the cube can change color on respawn or not
	UFUNCTION(BlueprintCallable, category = "Cube")
	void SetMaintainColorOnRespawn(bool changeBehaviour);

	// Return if the cube change location on respawn or not
	UFUNCTION(BlueprintCallable, category = "Cube")
	bool GetUseStartingLocationOnRespawn();

	// Edit if the cube change location on respawn or not
	UFUNCTION(BlueprintCallable, category = "Cube")
	void SetUseStartingLocationOnRespawn(bool changeBehaviour);

	// Return if the cube can be destroyed or not
	UFUNCTION(BlueprintCallable, category = "Cube")
	bool GetCanBeDestroyed();

	// Edit if the cube can be destroyed or not
	UFUNCTION(BlueprintCallable, category = "Cube")
	void SetCanBeDestroyed(bool changeBehaviour);

	//UFUNCTION(BlueprintCallable, Category=Cube)
	virtual void InterfacedDestroy() override;

	UFUNCTION(BlueprintCallable, category = "Cube")
	virtual void InterfacedDestroy(FVector HitLocation, FVector NormalImpulse) override;

	// To apply editor changes at realtime
	virtual void OnConstruction(const FTransform& Transform) override;

	// On actor transform move in editor
	virtual void PostEditMove(bool bFinished) override;
};
