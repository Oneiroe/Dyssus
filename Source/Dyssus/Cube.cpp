// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "Cube.h"
#include "ColorableFactory.h"
#include "UnrealString.h"

ACube::ACube()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->bGenerateOverlapEvents = true;
	
	CanBeDestroyed = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	DestructibleMesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleMesh"));

	CubeMesh = StaticMesh;
	Cast<UStaticMeshComponent>(CubeMesh)->SetSimulatePhysics(true);
	SetRootComponent(Cast<UStaticMeshComponent>(CubeMesh));
	BoxComponent->AttachParent = Cast<UStaticMeshComponent>(CubeMesh);
}

void ACube::OnConstruction(const FTransform& Transform)
{
	DestructibleMesh->SetDestructibleMesh(DMesh);
	StaticMesh->SetStaticMesh(SMesh);

	if (CanBeDestroyed && DestructibleMesh)
	{
		CubeMesh = DestructibleMesh;

		Cast<UDestructibleComponent>(CubeMesh)->SetSimulatePhysics(true);

		SetRootComponent(Cast<UDestructibleComponent>(CubeMesh));
		BoxComponent->AttachParent = Cast<UDestructibleComponent>(CubeMesh);
	}
	else if (StaticMesh)
	{
		CubeMesh = StaticMesh;

		Cast<UStaticMeshComponent>(CubeMesh)->SetSimulatePhysics(true);

		SetRootComponent(Cast<UStaticMeshComponent>(CubeMesh));
		BoxComponent->AttachParent = Cast<UStaticMeshComponent>(CubeMesh);
	}

	SetColor(DColor);
}

void ACube::PostEditMove(bool bFinished)
{
	UE_LOG(LogTemp, Warning, TEXT("ACube->PostEditMove"));
	StartingLocation = RootComponent->GetComponentTransform().GetLocation();
	if (UseStartingLocationOnRespawn == true) RespawnLocation = StartingLocation;
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

TEnumAsByte<DTypes::DCOLOR> ACube::GetDefaultColor()
{
	return DDefaultColor;
}

void ACube::SetDefaultColor(DTypes::DCOLOR color)
{
	DDefaultColor = color;
}

bool ACube::GetCanChangeColor()
{
	return CanChangeColor;
}

void ACube::SetCanChangeColor(bool changeBehaviour)
{
	CanChangeColor = changeBehaviour;
}

FVector ACube::GetStartingLocation()
{
	return StartingLocation;
}

// REMOVE-PENDING
void ACube::SetStartingLocation(FVector newStartingLocation)
{
	StartingLocation = newStartingLocation;
}

FVector ACube::GetRespawnLocation()
{
	return RespawnLocation;
}

void ACube::SetRespawnLocation(FVector new_location)
{
	RespawnLocation = new_location;
}

bool ACube::GetRespawnable()
{
	return Respawnable;
}

void ACube::SetRespawnable(bool changeBehaviour)
{
	Respawnable = changeBehaviour;
}

bool ACube::GetMaintainColorOnRespawn()
{
	return MaintainColorOnRespawn;
}

void ACube::SetMaintainColorOnRespawn(bool changeBehaviour)
{
	MaintainColorOnRespawn = changeBehaviour;
}

bool ACube::GetUseStartingLocationOnRespawn()
{
	return UseStartingLocationOnRespawn;
}

void ACube::SetUseStartingLocationOnRespawn(bool changeBehaviour)
{
	UseStartingLocationOnRespawn = changeBehaviour;
}

bool ACube::GetCanBeDestroyed()
{
	return CanBeDestroyed;
}

void ACube::SetCanBeDestroyed(bool changeBehaviour)
{
	CanBeDestroyed = changeBehaviour;
}

void ACube::InterfacedDestroy()
{
	this->Destroy();
	
	if (Respawnable) RespawnCube();
}

void ACube::InterfacedDestroy(FVector HitLocation, FVector NormalImpulse)
{
	if (!CanBeDestroyed) return;

	GetWorldTimerManager().SetTimer(this, &ACube::InterfacedDestroy, 2.0f);

	FTransform destructionTransform = GetRootComponent()->GetComponentTransform();
	if (MaintainColorOnRespawn == true) DDefaultColor = GetColor();

	GetRootComponent()->DestroyComponent();

	CubeMesh = NewObject<UDestructibleComponent>(this);
	Cast<UDestructibleComponent>(CubeMesh)->SetWorldTransform(destructionTransform);

	Cast<UDestructibleComponent>(CubeMesh)->SetSimulatePhysics(true);
	Cast<UDestructibleComponent>(CubeMesh)->SetMaterial(0, Material);
	Cast<UDestructibleComponent>(CubeMesh)->RegisterComponent();

	SetRootComponent(Cast<UDestructibleComponent>(CubeMesh));
	RootComponent->SetVisibility(true);

	Cast<UDestructibleComponent>(CubeMesh)->ApplyRadiusDamage(10.0, HitLocation, 2.0, 5.0, false);
	this->SetActorEnableCollision(false);
	Cast<UDestructibleComponent>(CubeMesh)->SetCollisionProfileName(TEXT("OverlapAll"));
}


void ACube::RespawnCube()
{
	FVector location;
	if (UseStartingLocationOnRespawn == true) location = StartingLocation;
	else location = RespawnLocation;
	ACube* respawnedCube = (ACube*)GetWorld()->SpawnActor(ACube::StaticClass(), &location);

	respawnedCube->SetCanChangeColor(CanChangeColor);

	respawnedCube->SetDefaultColor(DDefaultColor);

	respawnedCube->SetStartingLocation(location);
	respawnedCube->SetRespawnLocation(RespawnLocation);
	respawnedCube->SetRespawnable(Respawnable);
	respawnedCube->SetMaintainColorOnRespawn(MaintainColorOnRespawn);
	respawnedCube->SetCanBeDestroyed(CanBeDestroyed);
	respawnedCube->SetUseStartingLocationOnRespawn(UseStartingLocationOnRespawn);
	respawnedCube->CubeMesh = CubeMesh;
}

void ACube::SetColor(DTypes::DCOLOR dColor)
{
	DColor = dColor;

	if (CubeMaterials.Num() > DColor)
	{
		Material = CubeMaterials[DColor];

		if (CanBeDestroyed) Cast<UDestructibleComponent>(CubeMesh)->SetMaterial(0, Material);
		else Cast<UStaticMeshComponent>(CubeMesh)->SetMaterial(0, Material);
	}
}

DTypes::DCOLOR ACube::GetColor()
{
	return DColor;
}