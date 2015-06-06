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

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeAsset(TEXT("/Game/Dyssus/Meshes/Shape_Cube_Changable_Color.Shape_Cube_Changable_Color"));
	//changableColorCubeMesh = cubeAsset.Object;
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> cubePermanentAsset(TEXT("/Game/Dyssus/Meshes/Shape_Cube_Permanent.Shape_Cube_Permanent"));
	//permanentColorCubeMesh = cubePermanentAsset.Object;

	//static ConstructorHelpers::FObjectFinder<UDestructibleMesh> cubeDestroyableAsset(TEXT("/Game/Dyssus/Meshes/Shape_Cube_Changable_Color_DM.Shape_Cube_Changable_Color_DM"));
	//destroyableChangableColorCubeMesh = cubeDestroyableAsset.Object;
	//static ConstructorHelpers::FObjectFinder<UDestructibleMesh> cubePermanentDestroyableAsset(TEXT("/Game/Dyssus/Meshes/Shape_Cube_Permanent_DM.Shape_Cube_Permanent_DM"));
	//destroyablePermanentColorCubeMesh = cubePermanentDestroyableAsset.Object;
	
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CubeRootComponent"));

	//UStaticMeshComponent* CubeMesh = NewObject<UStaticMeshComponent>(this);
	
	UStaticMeshComponent* CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	//RootComponent = CubeMesh;
	CubeMesh->SetSimulatePhysics(true);

	SetRootComponent(CubeMesh);
}

void ACube::OnConstruction(const FTransform& Transform)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->OnConstruction()"));
	TArray<UStaticMeshComponent*> Components;
	this->GetComponents<UStaticMeshComponent>(Components);
	if (canChangeColor == true){
		Components[0]->SetStaticMesh(changableColorCubeMesh);
	}
	else
	{
		Components[0]->SetStaticMesh(permanentColorCubeMesh);
	}
	Components[0]->SetMaterial(0, defaultColor);
}

void ACube::PostEditMove(bool bFinished)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->PostEditMove"));
	startingLocation = RootComponent->GetComponentTransform().GetLocation();
	if (useStartingLocationOnRespawn == true) respawnLocation = startingLocation;
}

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

UMaterial* ACube::getCurrentColor()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->getCurrentColor()"));
	//return this->GetDestructibleComponent()->GetMaterial(0)->GetMaterial();
	TArray<UStaticMeshComponent*> Components;
	this->GetComponents<UStaticMeshComponent>(Components);
	if (Components.Num() < 1) return defaultColor;
	return Components[0]->GetMaterial(0)->GetMaterial();
}

void ACube::setCurrentColor(UMaterial* newCurrentColor)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->setCurrentColor()"));
	//print("ACube->setCurrentColor()");
	//this->GetDestructibleComponent()->SetMaterial(0, newCurrentColor);
	TArray<UStaticMeshComponent*> Components;
	this->GetComponents<UStaticMeshComponent>(Components);
	if (Components.Num() < 1) return;
	Components[0]->SetMaterial(0, newCurrentColor);
}

bool ACube::getCanChangeColor()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->getCanChangeColor()"));
	return canChangeColor;
}

void ACube::setCanChangeColor(bool changeBehaviour)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->setCanChangeColor()"));
	print("ACube->setCanChangeColor()");
	if (canChangeColor == changeBehaviour) return;
	
	TArray<UStaticMeshComponent*> Components;
	this->GetComponents<UStaticMeshComponent>(Components);
	if (Components.Num() < 1) return;
	if (changeBehaviour == true)
	{
		Components[0]->SetStaticMesh(changableColorCubeMesh);
	}
	else{
		Components[0]->SetStaticMesh(permanentColorCubeMesh);
	}
	canChangeColor = changeBehaviour;
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

void ACube::setCanBeDestroyed(bool changeBehaviour)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->setCanBeDestroyed()"));
	//print("ACube->setCanBeDestroyed()");
	
	canBeDestroyed = changeBehaviour;
}

//void ACube::ReceiveHit(
//	class UPrimitiveComponent * MyComp,
//	AActor * Other,
//	class UPrimitiveComponent * OtherComp,
//	bool bSelfMoved,
//	FVector HitLocation,
//	FVector HitNormal,
//	FVector NormalImpulse,
//	const FHitResult & Hit)
//{
//	UE_LOG(LogTemp, Warning, TEXT("ACube->HITevent()"));
//	print("ACube->HIT()");
//}


void ACube::interfacedDestroy()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->Destroy()"));
	this->Destroy();
	if (respawnable)
	{
		respawnCube();
	}
}
	
void ACube::interfacedDestroy(FVector HitLocation, FVector NormalImpulse)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACube->Destroy()"));
		
		if (canBeDestroyed == false) return;
		
		TArray<UStaticMeshComponent*> Components;
		this->GetComponents<UStaticMeshComponent>(Components);
		if (Components.Num() < 1) return;

		GetWorldTimerManager().SetTimer(this, &ACube::interfacedDestroy, 2.0f);
		
		FTransform destructionTransform = Components[0]->GetComponentTransform();
		if (maintainColorOnRespawn == true)
		{
			defaultColor = getCurrentColor();
		}
		UMaterial* currentColor = getCurrentColor();
		Components[0]->DestroyComponent();

		UDestructibleComponent* cubeDestroyableMesh = NewObject<UDestructibleComponent>(this);
		cubeDestroyableMesh->SetWorldTransform(destructionTransform);
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
		cubeDestroyableMesh->SetMaterial(1, currentColor);
		cubeDestroyableMesh->RegisterComponent();
		SetRootComponent(cubeDestroyableMesh);
		RootComponent->SetVisibility(true);
		//cubeDestroyableMesh->ApplyDamage(float DamageAmount, const FVector & HitLocation, const FVector & ImpulseDir, float ImpulseStrength);
		//cubeDestroyableMesh->ApplyDamage(5.0, HitLocation, NormalImpulse, 5.0);
		//void ApplyRadiusDamage(float BaseDamage,	const FVector & HurtOrigin,	float DamageRadius,	float ImpulseStrength,	bool bFullDamage)
		cubeDestroyableMesh->ApplyRadiusDamage(10.0, HitLocation, 2.0, 5.0, false);
		this->SetActorEnableCollision(false);
		cubeDestroyableMesh->SetCollisionProfileName(TEXT("OverlapAll"));
		//cubeDestroyableMesh->SetCollisionEnabled(false);;
		//float startTime = GetWorld()->TimeSeconds;
		//this->AActor::Destroy();
	}


void ACube::respawnCube()
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->respawnCube()"));
	
	FVector location;
	if (useStartingLocationOnRespawn == true)
	{
		location=startingLocation;
	}
	else
	{
		location = respawnLocation;		
	}
	ACube* respawnedCube = (ACube*)GetWorld()->SpawnActor(ACube::StaticClass(), &location);
	
	respawnedCube->setCanChangeColor(canChangeColor);	
	TArray<UStaticMeshComponent*> Components;
	respawnedCube->GetComponents<UStaticMeshComponent>(Components);
	if (Components.Num() < 1) return;
	if (canChangeColor == true)
	{
		Components[0]->SetStaticMesh(changableColorCubeMesh);
	}
	else
	{
		Components[0]->SetStaticMesh(permanentColorCubeMesh);
	}
	//if (maintainColorOnRespawn == true)
	//{
	//	Components[0]->SetMaterial(0, defaultColor);
	//}
	//else
	//{
	//	Components[0]->SetMaterial(0, defaultColor);
	//}
	
	Components[0]->SetMaterial(0, defaultColor);

	respawnedCube->setDefaultColor(defaultColor);

	respawnedCube->setStartingLocation(location);
	respawnedCube->setRespawnLocation(respawnLocation);
	respawnedCube->setRespawnable(respawnable);
	respawnedCube->setMaintainColorOnRespawn(maintainColorOnRespawn);
	respawnedCube->setCanBeDestroyed(canBeDestroyed);
	respawnedCube->setUseStartingLocationOnRespawn(useStartingLocationOnRespawn);
	respawnedCube->changableColorCubeMesh = changableColorCubeMesh;
	respawnedCube->permanentColorCubeMesh = permanentColorCubeMesh;
	respawnedCube->destroyableChangableColorCubeMesh = destroyableChangableColorCubeMesh;
	respawnedCube->destroyablePermanentColorCubeMesh = destroyablePermanentColorCubeMesh;
}