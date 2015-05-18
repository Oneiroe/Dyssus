// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "Cube.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Creating dummy root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CubeRootComponent"));

	// Initializing the real mesh of the cube and the default meshes for cubes and permanent cubes
	//cubeDestroyableMesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestroyableComponent"));
	//cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeAsset(TEXT("/Game/Dyssus/Meshes/Shape_Cube_Changable_Color.Shape_Cube_Changable_Color"));
	changableColorCubeMesh = cubeAsset.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cubePermanentAsset(TEXT("/Game/Dyssus/Meshes/Shape_Cube_Permanent.Shape_Cube_Permanent"));
	permanentColorCubeMesh = cubePermanentAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDestructibleMesh> cubeDestroyableAsset(TEXT("/Game/Dyssus/Meshes/Shape_Cube_Changable_Color_DM.Shape_Cube_Changable_Color_DM"));
	destroyableChangableColorCubeMesh = cubeDestroyableAsset.Object;
	static ConstructorHelpers::FObjectFinder<UDestructibleMesh> cubePermanentDestroyableAsset(TEXT("/Game/Dyssus/Meshes/Shape_Cube_Permanent_DM.Shape_Cube_Permanent_DM"));
	destroyablePermanentColorCubeMesh = cubePermanentDestroyableAsset.Object;

	startingLocation = RootComponent->GetComponentTransform().GetLocation();
	respawnLocation = startingLocation;
}

//void ACube::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
void ACube::OnConstruction(const FTransform& Transform)
{
	//	Super::OnConstruction(Transform);
	if (RootComponent->GetChildComponent(0)) RootComponent->GetChildComponent(0)->DestroyComponent();
	if (canBeDestroyed == true)
	{
		UDestructibleComponent* cubeDestroyableMesh = NewObject<UDestructibleComponent>(this);
		if (canChangeColor == true)
		{
			cubeDestroyableMesh->SetDestructibleMesh(destroyableChangableColorCubeMesh);
		}
		else
		{
			cubeDestroyableMesh->SetDestructibleMesh(destroyablePermanentColorCubeMesh);
		}
		cubeDestroyableMesh->SetSimulatePhysics(true);
		cubeDestroyableMesh->SetMaterial(0, defaultColor);
		cubeDestroyableMesh->AttachTo(RootComponent);
		cubeDestroyableMesh->RegisterComponent();
	}
	else
	{
		UStaticMeshComponent* cubeMesh = NewObject<UStaticMeshComponent>(this);
		
		if (canChangeColor == true)
		{
			cubeMesh->SetStaticMesh(changableColorCubeMesh);
		}
		else
		{
			cubeMesh->SetStaticMesh(permanentColorCubeMesh);
		}
		cubeMesh->SetSimulatePhysics(true);
		cubeMesh->SetMaterial(0, defaultColor);
		cubeMesh->AttachTo(RootComponent);
		cubeMesh->RegisterComponent();
	}
}


void ACube::PostEditMove(bool bFinished)
{
	//Super::PostEditMove(bFinished);
	startingLocation = RootComponent->GetComponentTransform().GetLocation();
	if (useStartingLocationOnRespawn == true) respawnLocation = startingLocation;
}


// executed immediately before gameplay begins
void ACube::PreInitializeComponents()
{
	if (RootComponent->GetChildComponent(0)) RootComponent->GetChildComponent(0)->DestroyComponent();
	if (canBeDestroyed == true)
	{
		UDestructibleComponent* cubeDestroyableMesh = NewObject<UDestructibleComponent>(this);
		if (canChangeColor == true)
		{
			cubeDestroyableMesh->SetDestructibleMesh(destroyableChangableColorCubeMesh);
		}
		else
		{
			cubeDestroyableMesh->SetDestructibleMesh(destroyablePermanentColorCubeMesh);
		}
		cubeDestroyableMesh->SetSimulatePhysics(true);
		cubeDestroyableMesh->SetMaterial(0, defaultColor);
		cubeDestroyableMesh->AttachTo(RootComponent);
		cubeDestroyableMesh->RegisterComponent();
	}
	else
	{
		UStaticMeshComponent* cubeMesh = NewObject<UStaticMeshComponent>(this);

		if (canChangeColor == true)
		{
			cubeMesh->SetStaticMesh(changableColorCubeMesh);
		}
		else
		{
			cubeMesh->SetStaticMesh(permanentColorCubeMesh);
		}
		cubeMesh->SetSimulatePhysics(true);
		cubeMesh->SetMaterial(0, defaultColor);
		cubeMesh->AttachTo(RootComponent);
		cubeMesh->RegisterComponent();
	}
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACube::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

UMaterial* ACube::getDefaultColor()
{
	return defaultColor;
}

void ACube::setDefaultColor(UMaterial* newDefaultColor)
{
	defaultColor = newDefaultColor;
}

//TO-DO
UMaterial* ACube::getCurrentColor()
{
	//UMaterial* res = cubeMesh->GetMaterial(0)->GetMaterial();
	return NULL;
}

//TO-DO
void ACube::setCurrentColor(UMaterial* newCurrentColor)
{
	//cubeMesh->SetMaterial(0, newCurrentColor);
}

bool ACube::getCanChangeColor()
{
	return canChangeColor;
}

//TO-DO
void ACube::setCanChangeColor(bool changeBehaviour)
{
	canChangeColor = changeBehaviour;
	//if (canChangeColor == true)
	//{
	//	cubeMesh->SetStaticMesh(changableColorCubeMesh);
	//}
	//else
	//{
	//	cubeMesh->SetStaticMesh(permanentColorCubeMesh);
	//}
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

bool ACube::getMaintainColorOnRespawn()
{
	return maintainColorOnRespawn;
}

void ACube::setMaintainColorOnRespawn(bool changeBehaviour)
{
	maintainColorOnRespawn = changeBehaviour;
}

//bool getUseStartingLocationOnRespawn()
//{
//	return useStartingLocationOnRespawn;
//}
//
//void setUseStartingLocationOnRespawn(bool changeBehaviour)
//{
//	useStartingLocationOnRespawn = changeBehaviour;
//}

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

