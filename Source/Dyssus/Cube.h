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

	bool HasDM;

	UMaterial* Material;

	/** Whether this cube can change color */
	UPROPERTY(EditAnywhere)
	bool CanChangeColor;

	// Initial location of the cube on level start
	UPROPERTY(VisibleAnywhere)
	FVector StartingLocation;

	/** Initial rotation of the cube on level start */
	UPROPERTY(VisibleAnywhere)
	FRotator StartingRotation;

	// Location of the cube on respawn
	UPROPERTY(EditAnywhere)
	FVector RespawnLocation;

	// Rotation of the cube on respawn
	UPROPERTY(EditAnywhere)
	FRotator RespawnRotation;

	/** Whether this cube is respawnable */
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

public:

	/** Static mesh of the cube */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rendering)
	class UStaticMesh* SMesh;

	/** Destructible component of the cube */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rendering)
	class UDestructibleMesh* DMesh;

	/** Default color of the cube */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	TEnumAsByte<DTypes::DCOLOR> DDefaultColor;

	/** Current color of the cube */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	TEnumAsByte<DTypes::DCOLOR> DColor;

	/** Returns the current color of the cube */
	UFUNCTION(BlueprintCallable, Category = Colors)
	virtual DTypes::DCOLOR GetColor() override;

	/** Sets the color of the cube */
	UFUNCTION(BlueprintCallable, Category = Colors)
	virtual void SetColor(DTypes::DCOLOR dColor_) override;

	/** Array of cube materials, one per each color */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	TArray<UMaterial*> CubeMaterials;

	/** Explosion parameters */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	float BaseDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	float DamageRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	float ImpulseStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	bool CanBeDestroyed;

	class UStaticMeshComponent* StaticMesh;

	class UDestructibleComponent* DestructibleMesh;

	// Sets default values for this actor's properties
	ACube();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//UFUNCTION(BlueprintCallable, Category=Cube)
	virtual void InterfacedDestroy() override;

	/** Called when it's time to destroy this cube */
	UFUNCTION(BlueprintCallable, category = "Cube")
	virtual void InterfacedDestroy(FVector HitLocation, FVector NormalImpulse) override;

	// To apply editor changes at realtime
	virtual void OnConstruction(const FTransform& Transform) override;
};
