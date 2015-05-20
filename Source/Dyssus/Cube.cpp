// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "Cube.h"
#include "UnrealString.h"
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

// Sets default values
ACube::ACube()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->constructor"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	
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

	//startingLocation = RootComponent->GetComponentTransform().GetLocation();
	//respawnLocation = startingLocation;
}

//void ACube::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
void ACube::OnConstruction(const FTransform& Transform)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->OnConstruction"));
	//	Super::OnConstruction(Transform);
	UE_LOG(LogTemp, Warning, TEXT("ACube->OnConstruction->cube components:%d"), RootComponent->GetNumChildrenComponents());

	//if (RootComponent->GetChildComponent(0)) RootComponent->GetChildComponent(0)->DestroyComponent();
	if (RootComponent->GetNumChildrenComponents()>0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACube->OnConstruction->removing %d child components"), RootComponent->GetNumChildrenComponents());
		TArray< USceneComponent * > components;
		RootComponent->GetChildrenComponents(true, components);
		for (int i = 0; i < RootComponent->GetNumChildrenComponents(); i++)
		{
			components[i]->DestroyComponent();
		}
		UE_LOG(LogTemp, Warning, TEXT("ACube->OnConstruction->DONE! remaining child components: %d"), RootComponent->GetNumChildrenComponents());
	}
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

// executed any time the object is moved in the editor
void ACube::PostEditMove(bool bFinished)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->PostEditMove"));
	//Super::PostEditMove(bFinished);
	startingLocation = RootComponent->GetComponentTransform().GetLocation();
	if (useStartingLocationOnRespawn == true) respawnLocation = startingLocation;
}

// executed immediately before gameplay begins
void ACube::PreInitializeComponents()
{
	UE_LOG(LogTemp, Warning, TEXT("PreInitializeComponents"));
	
	UE_LOG(LogTemp, Warning, TEXT("PreInitializeComponents->cube components:%d"), RootComponent->GetNumChildrenComponents());

	if (RootComponent->GetChildComponent(0))
	{
		UE_LOG(LogTemp, Warning, TEXT("PreInitializeComponents->precedent component found"));
		RootComponent->GetChildComponent(0)->DestroyComponent();
	}
	
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
	UE_LOG(LogTemp, Warning, TEXT("PLAY>cube components:%d"), RootComponent->GetNumChildrenComponents());

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

//TO-VERIFY
UMaterial* ACube::getCurrentColor()
{
	//UMaterial* res = cubeMesh->GetMaterial(0)->GetMaterial();
	if (canBeDestroyed == true)
	{
		UDestructibleComponent* myComponent = Cast<UDestructibleComponent>(RootComponent->GetChildComponent(0));
		return myComponent->GetMaterial(0)->GetMaterial();
	}
	else
	{
		UStaticMeshComponent* myComponent = Cast<UStaticMeshComponent>(RootComponent->GetChildComponent(0));
		return myComponent->GetMaterial(0)->GetMaterial();
	}
}

//TO-VERIFY
void ACube::setCurrentColor(UMaterial* newCurrentColor)
{
	if (canChangeColor == false) return;
	if (canBeDestroyed == true)
	{
		UDestructibleComponent* myComponent=Cast<UDestructibleComponent>(RootComponent->GetChildComponent(0));
		myComponent->SetMaterial(0,newCurrentColor);
	}
	else
	{
		UStaticMeshComponent* myComponent = Cast<UStaticMeshComponent>(RootComponent->GetChildComponent(0));
		myComponent->SetMaterial(0, newCurrentColor);
	}
}

bool ACube::getCanChangeColor()
{
	return canChangeColor;
}

//TO-VERIFY
void ACube::setCanChangeColor(bool changeBehaviour)
{
	if (canChangeColor == changeBehaviour) return;

	if (canBeDestroyed == true)
	{
		UDestructibleComponent* cubeDestroyableMesh = Cast<UDestructibleComponent>(RootComponent->GetChildComponent(0));
		if (changeBehaviour == true)
		{
			cubeDestroyableMesh->SetDestructibleMesh(destroyableChangableColorCubeMesh);
		}
		else
		{
			cubeDestroyableMesh->SetDestructibleMesh(destroyablePermanentColorCubeMesh);
		}
	}
	else
	{
		UStaticMeshComponent* cubeMesh = Cast<UStaticMeshComponent>(RootComponent->GetChildComponent(0));

		if (changeBehaviour == true)
		{
			cubeMesh->SetStaticMesh(changableColorCubeMesh);
		}
		else
		{
			cubeMesh->SetStaticMesh(permanentColorCubeMesh);
		}
	}
	canChangeColor = changeBehaviour;
}

FVector ACube::getStartingLocation()
{
	return startingLocation;
}

// REMOVE-PENDING
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

bool ACube::getUseStartingLocationOnRespawn()
{
	return useStartingLocationOnRespawn;
}

void ACube::setUseStartingLocationOnRespawn(bool changeBehaviour)
{
	useStartingLocationOnRespawn = changeBehaviour;
}

bool ACube::getCanBeDestroyed()
{
	return canBeDestroyed;
}

//TO-VERIFY
void ACube::setCanBeDestroyed(bool changeBehaviour)
{
	if (canBeDestroyed == changeBehaviour) return;

	UMaterial* currentColor = getCurrentColor();
	if (RootComponent->GetChildComponent(0)) RootComponent->GetChildComponent(0)->DestroyComponent();
	
	if (changeBehaviour == true)
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
		cubeDestroyableMesh->SetMaterial(0, currentColor);
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
		cubeMesh->SetMaterial(0, currentColor);
		cubeMesh->AttachTo(RootComponent);
		cubeMesh->RegisterComponent();
	}
	canBeDestroyed = changeBehaviour;
}

//TO-DO
void ACube::Destroy()
{
	if (canBeDestroyed == false) return;
	if (respawnable)
	{
		respawnCube();
	}
	else
	{
		
	}
}

//TO-DO
void ACube::respawnCube()
{

}