// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "Cube.h"
#include "UnrealString.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

// Sets default values
//ACube::ACube()
//{
//	UE_LOG(LogTemp, Warning, TEXT("ACube->constructor"));
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	//PrimaryActorTick.bCanEverTick = true;
//
//	//static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeAsset(TEXT("/Game/Dyssus/Meshes/Shape_Cube_Changable_Color.Shape_Cube_Changable_Color"));
//	//changableColorCubeMesh = cubeAsset.Object;
//	//static ConstructorHelpers::FObjectFinder<UStaticMesh> cubePermanentAsset(TEXT("/Game/Dyssus/Meshes/Shape_Cube_Permanent.Shape_Cube_Permanent"));
//	//permanentColorCubeMesh = cubePermanentAsset.Object;
//
//	//static ConstructorHelpers::FObjectFinder<UDestructibleMesh> cubeDestroyableAsset(TEXT("/Game/Dyssus/Meshes/Shape_Cube_Changable_Color_DM.Shape_Cube_Changable_Color_DM"));
//	//destroyableChangableColorCubeMesh = cubeDestroyableAsset.Object;
//	//static ConstructorHelpers::FObjectFinder<UDestructibleMesh> cubePermanentDestroyableAsset(TEXT("/Game/Dyssus/Meshes/Shape_Cube_Permanent_DM.Shape_Cube_Permanent_DM"));
//	//destroyablePermanentColorCubeMesh = cubePermanentDestroyableAsset.Object;
//
//}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("PLAY>cube components:%d"), RootComponent->GetNumChildrenComponents());

}

// Called every frame
void ACube::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

UMaterial* ACube::getDefaultColor()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->getDefaultColor()"));
	return defaultColor;
}

void ACube::setDefaultColor(UMaterial* newDefaultColor)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->setDefaultColor()"));
	defaultColor = newDefaultColor;
}

//TO-DO
//UMaterial* ACube::getCurrentColor()
//{
//	UE_LOG(LogTemp, Warning, TEXT("ACube->getCurrentColor()"));
//	print("ACube->getCurrentColor()");
//	//UMaterial* res = cubeMesh->GetMaterial(0)->GetMaterial();
//	//if (canBeDestroyed == true)
//	//{
//	//	UDestructibleComponent* myComponent = Cast<UDestructibleComponent>(RootComponent);
//	//	return myComponent->GetMaterial(0)->GetMaterial();
//	//}
//	//else
//	//{
//	//	UStaticMeshComponent* myComponent = Cast<UStaticMeshComponent>(RootComponent);
//	//	return myComponent->GetMaterial(0)->GetMaterial();
//	//}
//	return NULL;
//}

//TO-DO
//void ACube::setCurrentColor(UMaterial* newCurrentColor)
//{
//	UE_LOG(LogTemp, Warning, TEXT("ACube->setCurrentColor()"));
//	print("ACube->setCurrentColor()");
//	//if (canChangeColor == false) return;
//	//if (canBeDestroyed == true)
//	//{
//	//	UDestructibleComponent* myComponent=Cast<UDestructibleComponent>(RootComponent->GetChildComponent(0));
//	//	myComponent->SetMaterial(0,newCurrentColor);
//	//}
//	//else
//	//{
//	//	UStaticMeshComponent* myComponent = Cast<UStaticMeshComponent>(RootComponent->GetChildComponent(0));
//	//	myComponent->SetMaterial(0, newCurrentColor);
//	//}
//}

bool ACube::getCanChangeColor()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->getCanChangeColor()"));
	return canChangeColor;
}

//TO-DO
void ACube::setCanChangeColor(bool changeBehaviour)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->setCanChangeColor()"));
	print("ACube->setCanChangeColor()");
	
	/*if (canChangeColor == changeBehaviour) return;

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
	canChangeColor = changeBehaviour;*/
}

FVector ACube::getStartingLocation()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->getStartingLocation()"));
	return startingLocation;
}

// REMOVE-PENDING
void ACube::setStartingLocation(FVector newStartingLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->setStartingLocation()"));
	startingLocation = newStartingLocation;
}

FVector ACube::getRespawnLocation()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->getRespawnLocation()"));
	return respawnLocation;
}

void ACube::setRespawnLocation(FVector new_location)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->setRespawnLocation()"));
	respawnLocation = new_location;
}

bool ACube::getRespawnable()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->getRespawnable()"));
	return respawnable;
}

void ACube::setRespawnable(bool changeBehaviour)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->setRespawnable()"));
	respawnable = changeBehaviour;
}

bool ACube::getMaintainColorOnRespawn()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->getMaintainColorOnRespawn()"));
	return maintainColorOnRespawn;
}

void ACube::setMaintainColorOnRespawn(bool changeBehaviour)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->setMaintainColorOnRespawn()"));
	maintainColorOnRespawn = changeBehaviour;
}

bool ACube::getUseStartingLocationOnRespawn()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->getUseStartingLocationOnRespawn()"));
	return useStartingLocationOnRespawn;
}

void ACube::setUseStartingLocationOnRespawn(bool changeBehaviour)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->setUseStartingLocationOnRespawn()"));
	useStartingLocationOnRespawn = changeBehaviour;
}

bool ACube::getCanBeDestroyed()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->getCanBeDestroyed()"));
	return canBeDestroyed;
}

//TO-DO
void ACube::setCanBeDestroyed(bool changeBehaviour)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->setCanBeDestroyed()"));
	print("ACube->setCanBeDestroyed()");
	
	/*if (canBeDestroyed == changeBehaviour) return;

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
	canBeDestroyed = changeBehaviour;*/
}

//TO-DO
void ACube::Destroy()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->Destroy()"));
	print("ACube->Destroy()");
	//if (canBeDestroyed == false) return;
	//if (respawnable)
	//{
	//	respawnCube();
	//}
	//else
	//{
	//	
	//}
}

//TO-DO
void ACube::respawnCube()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->respawnCube()"));
	print("ACube->respawnCube()");
}