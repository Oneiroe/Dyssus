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

	class USceneComponent* SceneComponent;

	UMaterial* Material;

	UPROPERTY(EditAnywhere)
	bool CanChangeColor;

	// Initial location of the cube on level start
	UPROPERTY(VisibleAnywhere)
	FVector StartingLocation;

	UPROPERTY(VisibleAnywhere)
	FRotator StartingRotation;

	// Location that the cube will reach on respawn
	UPROPERTY(EditAnywhere)
	FVector RespawnLocation;

	UPROPERTY(EditAnywhere)
	FRotator RespawnRotation;

	UPROPERTY(EditAnywhere)
	bool Respawnable;

	// Default color on respawn?
	UPROPERTY(EditAnywhere)
	bool MaintainColorOnRespawn;

	// Define if the cube will be respawned at his starting location or at the respawn one
	UPROPERTY(EditAnywhere)
	bool UseStartingTransformOnRespawn;

	// Respawn/Destroy timeout
	UPROPERTY(EditAnywhere)
	float Timeout;

	// Respawns the cube with the property set on construction
	void RespawnCube();

	void EraseCube();

public:

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	TArray<UMaterial*> CubeMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	float DamageRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	float ImpulseStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	bool CanBeDestroyed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	class UPrimitiveComponent* CubeMesh;

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void SetCubeMesh();

	// Sets default values for this actor's properties
	ACube();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//UFUNCTION(BlueprintCallable, Category=Cube)
	virtual void InterfacedDestroy() override;

	UFUNCTION(BlueprintCallable, category = "Cube")
	virtual void InterfacedDestroy(FVector HitLocation, FVector NormalImpulse) override;

	// To apply editor changes at realtime
	virtual void OnConstruction(const FTransform& Transform) override;
};
