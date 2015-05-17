// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DestroyableInterface.h"
#include "GrabbableInterface.h"
//this MUST be le last include!
#include "Cube.generated.h"   
UCLASS(Blueprintable)
class DYSSUS_API ACube : public AActor, public IDestroyableInterface, public IGrabbableInterface
{
	GENERATED_BODY()

private:
	//FString pathChangeColorMesh = TEXT("/Game/Dyssus/Meshes/Shape_Cylinder.Shape_Cylinder");

	// mesh of a normal cube that can change color
	UPROPERTY(EditAnywhere)
		UStaticMesh* changableColorCubeMesh;

	//FString pathPermanentColorMesh = TEXT("/Game/Dyssus/Meshes/Shape_Cube.Shape_Cube");

	// mesh of a cube that can't change color
	UPROPERTY(EditAnywhere)
		UStaticMesh* permanentColorCubeMesh;

	// mesh component of the cube (variable which respect to "canChangeColor" variable)
	UPROPERTY()
		UStaticMeshComponent* cubeMesh;

	// material that define the inizial and default color of a cube
	UPROPERTY(EditAnywhere)
		UMaterial* defaultColor;

	// material that define the current color of a cube
	UMaterial* current_color;

	// define if the cube is a permanent one or not
	UPROPERTY(EditAnywhere)
		bool canChangeColor = true;

	// Initial location of the cube on level start
	UPROPERTY(VisibleAnywhere)
		FVector startingLocation;

	// location that the cube will reach on respawn
	UPROPERTY(EditAnywhere)
		FVector respawnLocation;

	// define if the cube will be respawned or permanently destroyed
	UPROPERTY(EditAnywhere)
		bool respawnable = true;

	// define if the cube will change the current color on respawn or not
	UPROPERTY(EditAnywhere)
		bool changeColorOnRespawn = false;

	// define if the cube can be destroyed or not
	UPROPERTY(EditAnywhere)
		bool canBeDestroyed = true;

	// define if the cube will be respawned at his starting location or at the respawn one
	//UPROPERTY(EditAnywhere)
	//bool change_location_on_respawn = true;

	// respawns the cube with the property set on construction
	void respawn();

public:
	// Sets default values for this actor's properties
	ACube();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//Costructors
	/*
	Cube(FColor defaultColor, FVector startingLocation);
	Cube(FColor defaultColor, FVector startingLocation, bool respawnable, bool changeColorOnRespawn, bool change_location_on_respawn);
	permanent_Cube(FColor defaultColor, FVector startingLocation);
	permanent_Cube(FColor defaultColor, FVector startingLocation, bool respawnable, bool changeColorOnRespawn, bool change_location_on_respawn);
	*/

	// Returns the default/initial color of the cube
	UMaterial* getDefaultColor();

	// Edit the default coloro of the cube
	void setDefaultColor(UMaterial* newDefaultColor);

	// Returns the current color of the cube
	UMaterial* getCurrentColor();

	// Edit the current color of the cube
	void setCurrentColor(UMaterial* newCurrentColor);

	// retruns if the cube can change color or is a permanent one
	bool getCanChangeColor();

	// make the cube color changing possible or not
	void setCanChangeColor(bool changeBehaviour);

	// return the starting location of the cube
	FVector getStartingLocation();

	// edit the starting location of the cube
	void setStartingLocation(FVector newStartingLocation);

	// return the respawn location
	FVector getRespawnLocation();

	// edit the respawn location
	void setRespawnLocation(FVector new_location);

	// returns if the cube can be respawned or not
	bool getRespawnable();

	// edit if the cube can be respawned or not
	void setRespawnable(bool changeBehaviour);

	// returnn if the cube change color on the respawn or not
	bool getChangeColorOnRespawn();

	// edit if the cube can change color on respawn or not
	void setChangeColorOnRespawn(bool changeBehaviour);

	// retrun if the cube can be destroyed or not
	bool getCanBeDestroyed();

	// edit if the cube can be destroyed or not
	void setCanBeDestroyed(bool changeBehaviour);

	// From IDestroyableInterface
	virtual void Destroy() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	// return if the cube change location on respawn or not
	//bool get_change_location_on_respawn();

	// edit if the cube change location on respawn or not
	//void set_change_location_on_respawn(bool changeBehaviour);

	//Mesh get_mesh();
	//void set_mesh(Mesh new_mesh);

	//void destroy(Collision_object collision);

};
