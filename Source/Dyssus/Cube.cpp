// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "Cube.h"


// Sets default values
ACube::ACube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating dummy root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CubeRootComponent"));

	// Initializing the real mesh of the cube and the default meshes for cubes and permanent cubes
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeAsset(TEXT("/Game/Dyssus/Meshes/Shape_Cube_Changable_Color.Shape_Cube_Changable_Color"));
	changableColorCubeMesh = cubeAsset.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cubePermanentAsset(TEXT("/Game/Dyssus/Meshes/Shape_Cube_Permanent.Shape_Cube_Permanent"));
	permanentColorCubeMesh = cubePermanentAsset.Object;

	// to let designer work initialyze the mesh to the changable one, it will be override on BeginPlay
	cubeMesh->SetStaticMesh(changableColorCubeMesh);

	// Attach the mesh the the root component
	cubeMesh->SetSimulatePhysics(true);
	cubeMesh->AttachTo(RootComponent);
	startingLocation = RootComponent->GetComponentTransform().GetLocation();
	respawnLocation = startingLocation;
}

// Constructor script launched at any changes of the object in the editor
void ACube::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (canChangeColor == true)
	{
		cubeMesh->SetStaticMesh(changableColorCubeMesh);
	}
	else
	{
		cubeMesh->SetStaticMesh(permanentColorCubeMesh);
	}
	startingLocation = RootComponent->GetComponentTransform().GetLocation();
	respawnLocation = startingLocation;
	cubeMesh->SetMaterial(0, defaultColor);
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UMaterial* ACube::getDefaultColor()
{
	return defaultColor;
}

void ACube::setDefaultColor(UMaterial* newDefaultColor)
{
	defaultColor = newDefaultColor;
}

UMaterial* ACube::getCurrentColor()
{
	UMaterial* res = cubeMesh->GetMaterial(0)->GetMaterial();
	return res;
}

void ACube::setCurrentColor(UMaterial* newCurrentColor)
{
	cubeMesh->SetMaterial(0, newCurrentColor);
}

bool ACube::getCanChangeColor()
{
	return canChangeColor;
}

void ACube::setCanChangeColor(bool changeBehaviour)
{
	canChangeColor = changeBehaviour;
	if (canChangeColor == true)
	{
		cubeMesh->SetStaticMesh(changableColorCubeMesh);
	}
	else
	{
		cubeMesh->SetStaticMesh(permanentColorCubeMesh);
	}
}

FVector ACube::getStartingLocation()
{
	return startingLocation;
}

void ACube::setStartingLocation(FVector newStartingLocation)
{
	startingLocation = newStartingLocation;
}

FVector ACube::getRespawnLocation()
{
	return respawnLocation;
}

void ACube::setRespawnLocation(FVector new_location)
{
	respawnLocation = new_location;
}

bool ACube::getRespawnable()
{
	return respawnable;
}

void ACube::setRespawnable(bool changeBehaviour)
{
	respawnable = changeBehaviour;
}

bool ACube::getChangeColorOnRespawn()
{
	return changeColorOnRespawn;
}
void ACube::setChangeColorOnRespawn(bool changeBehaviour)
{
	changeColorOnRespawn = changeBehaviour;
}

bool ACube::getCanBeDestroyed()
{
	return canBeDestroyed;
}

void ACube::setCanBeDestroyed(bool changeBehaviour)
{
	canBeDestroyed = changeBehaviour;
}

void ACube::Destroy()
{
	if (canBeDestroyed == false) return;
}
