// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DestroyableInterface.h"
#include "GrabbableInterface.h"
//#include "Engine/DestructibleMesh.h"
//this MUST be le last include!
#include "Cube.generated.h"
UCLASS(Blueprintable)
class DYSSUS_API ACube :  public AActor, public IDestroyableInterface, public IGrabbableInterface
{ //public ADestructibleActor
	GENERATED_BODY()

private:
	//FString pathChangeColorMesh = TEXT("/Game/Dyssus/Meshes/Shape_Cylinder.Shape_Cylinder");
	
	// material that define the inizial and default color of a cube
	UPROPERTY(EditAnywhere)
	UMaterial* defaultColor;

	// material that define the current color of a cube
	//UMaterial* current_color;

	// define if the cube is a permanent one or not
	UPROPERTY(EditAnywhere)
	bool canChangeColor;
	//bool canChangeColor = true;

	// Initial location of the cube on level start
	UPROPERTY(VisibleAnywhere)
	FVector startingLocation;

	// location that the cube will reach on respawn
	UPROPERTY(EditAnywhere)
	FVector respawnLocation;

	// define if the cube will be respawned or permanently destroyed
	UPROPERTY(EditAnywhere)
	bool respawnable;
	//bool respawnable=true;
	
	// define if the cube will maintain the current color on respawn or turn back tu the default one
	UPROPERTY(EditAnywhere)
	bool maintainColorOnRespawn;
	//bool maintainColorOnRespawn = false;

	// define if the cube can be destroyed or not
	UPROPERTY(EditAnywhere)
	bool canBeDestroyed;
	//bool canBeDestroyed = true;

	// define if the cube will be respawned at his starting location or at the respawn one
	UPROPERTY(EditAnywhere)
	bool useStartingLocationOnRespawn;
	//bool useStartingLocationOnRespawn = true;

	// respawns the cube with the property set on construction
	void respawnCube();

public:	

	// mesh of a normal cube that can change color
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* changableColorCubeMesh;

	//FString pathPermanentColorMesh = TEXT("/Game/Dyssus/Meshes/Shape_Cube.Shape_Cube");

	// mesh of a cube that can't change color
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* permanentColorCubeMesh;

	// mesh of an destroyable cube that can change color
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDestructibleMesh* destroyableChangableColorCubeMesh;

	// mesh of an destroyable cube that can't change color
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDestructibleMesh* destroyablePermanentColorCubeMesh;

	// Sets default values for this actor's properties
	ACube();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;



	//Costructors
	/*
	Cube(FColor defaultColor, FVector startingLocation);
	Cube(FColor defaultColor, FVector startingLocation, bool respawnable, bool maintainColorOnRespawn, bool change_location_on_respawn);
	permanent_Cube(FColor defaultColor, FVector startingLocation);
	permanent_Cube(FColor defaultColor, FVector startingLocation, bool respawnable, bool maintainColorOnRespawn, bool change_location_on_respawn);
	*/
	
	// Returns the default/initial color of the cube
	UFUNCTION(BlueprintCallable,category="Cube")
	UMaterial* getDefaultColor();

	// Edit the default coloro of the cube
	UFUNCTION(BlueprintCallable,category="Cube")
	void setDefaultColor(UMaterial* newDefaultColor);
	
	// Returns the current color of the cube
	UFUNCTION(BlueprintCallable, category = "Cube")
	UMaterial* getCurrentColor();

	// Edit the current color of the cube
	UFUNCTION(BlueprintCallable, category = "Cube")
	void setCurrentColor(UMaterial* newCurrentColor);

	// retruns if the cube can change color or is a permanent one
	UFUNCTION(BlueprintCallable,category="Cube")
	bool getCanChangeColor();

	// make the cube color changing possible or not
	UFUNCTION(BlueprintCallable,category="Cube")
	void setCanChangeColor(bool changeBehaviour);
	
	// return the starting location of the cube
	UFUNCTION(BlueprintCallable,category="Cube")
	FVector getStartingLocation();

	// edit the starting location of the cube
	UFUNCTION(BlueprintCallable,category="Cube")
	void setStartingLocation(FVector newStartingLocation);//REMOVE-PENDING

	// return the respawn location
	UFUNCTION(BlueprintCallable,category="Cube")
	FVector getRespawnLocation();

	// edit the respawn location
	UFUNCTION(BlueprintCallable,category="Cube")
	void setRespawnLocation(FVector new_location);

	// returns if the cube can be respawned or not
	UFUNCTION(BlueprintCallable,category="Cube")
	bool getRespawnable();
	
	// edit if the cube can be respawned or not
	UFUNCTION(BlueprintCallable,category="Cube")
	void setRespawnable(bool changeBehaviour);

	// returnn if the cube change color on the respawn or not
	UFUNCTION(BlueprintCallable,category="Cube")
	bool getMaintainColorOnRespawn();

	// edit if the cube can change color on respawn or not
	UFUNCTION(BlueprintCallable,category="Cube")
	void setMaintainColorOnRespawn(bool changeBehaviour);

	// return if the cube change location on respawn or not
	UFUNCTION(BlueprintCallable,category="Cube")
	bool getUseStartingLocationOnRespawn();

	// edit if the cube change location on respawn or not
	UFUNCTION(BlueprintCallable,category="Cube")
	void setUseStartingLocationOnRespawn(bool changeBehaviour);

	// retrun if the cube can be destroyed or not
	UFUNCTION(BlueprintCallable,category="Cube")
	bool getCanBeDestroyed();

	// edit if the cube can be destroyed or not
	UFUNCTION(BlueprintCallable,category="Cube")
	void setCanBeDestroyed(bool changeBehaviour);

	// From IDestroyableInterface
	//UFUNCTION(BlueprintCallable, category = "Cube")
	virtual void MyDestroy() override;

	UFUNCTION(BlueprintCallable, category = "Cube")
	virtual void MyDestroy(FVector HitLocation, FVector NormalImpulse) override;

	// To apply editor changes at realtime
	virtual void OnConstruction(const FTransform& Transform) override;
	
	// executed immediately before gameplay begins
	//virtual void PreInitializeComponents() override;

	// other editor modifier
	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	// on actor transform move in editor
	virtual void PostEditMove(bool bFinished) override;

	//void destroy(Collision_object collision);
	
	// Called when trows hit collision
	//virtual void ReceiveHit(
	//class UPrimitiveComponent * MyComp,
	//	AActor * Other,
	//class UPrimitiveComponent * OtherComp,
	//	bool bSelfMoved,
	//	FVector HitLocation,
	//	FVector HitNormal,
	//	FVector NormalImpulse,
	//	const FHitResult & Hit
	//	) override;
};
