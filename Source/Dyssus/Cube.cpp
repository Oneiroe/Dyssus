// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "Cube.h"
#include "ColorableFactory.h"
#include "UnrealString.h"

ACube::ACube()
{
	CanBeDestroyed = false;

	BaseDamage = 100.f;
	DamageRadius = 20.f;
	ImpulseStrength = 15.f;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
}

void ACube::OnConstruction(const FTransform& Transform)
{
	if (CubeMesh)
	{
		CubeMesh->UnregisterComponent();
		CubeMesh->DestroyComponent();
	}

	if (CanBeDestroyed)
	{
		CubeMesh = ConstructObject<UDestructibleComponent>(UDestructibleComponent::StaticClass(), this, TEXT("DestructibleMesh"));
		Cast<UDestructibleComponent>(CubeMesh)->SetDestructibleMesh(DMesh);
	}
	else
	{
		CubeMesh = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this, TEXT("StaticMesh"));
		Cast<UStaticMeshComponent>(CubeMesh)->SetStaticMesh(SMesh);
	}

	CubeMesh->OnComponentCreated();
	if (CubeMesh->bWantsInitializeComponent) CubeMesh->InitializeComponent();
	CubeMesh->RegisterComponent();

	CubeMesh->bGenerateOverlapEvents = true;
	if(!CanBeDestroyed) CubeMesh->SetSimulatePhysics(true); // DM generates warnings
	CubeMesh->AttachTo(RootComponent);
	CubeMesh->SetRelativeLocation(FVector::ZeroVector);
	CubeMesh->SetRelativeRotation(FRotator::ZeroRotator);

	SetColor(DColor);
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();

	StartingLocation = RootComponent->GetComponentTransform().GetLocation();
	StartingRotation = RootComponent->GetComponentTransform().GetRotation().Rotator();

	if (UseStartingTransformOnRespawn == true)
	{
		RespawnLocation = StartingLocation;
		RespawnRotation = StartingRotation;
	}
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

void ACube::InterfacedDestroy()
{
	this->Destroy();

	if (Respawnable) RespawnCube();
}

void ACube::InterfacedDestroy(FVector HitLocation, FVector NormalImpulse)
{
	if (!CanBeDestroyed) return;

	Cast<UDestructibleComponent>(CubeMesh)->ApplyRadiusDamage(BaseDamage, HitLocation, DamageRadius, ImpulseStrength, false);
	this->SetActorEnableCollision(false);
	Cast<UDestructibleComponent>(CubeMesh)->SetCollisionProfileName(TEXT("OverlapAll"));

	GetWorldTimerManager().SetTimer(this, &ACube::RespawnCube, 2.0f);
}


void ACube::RespawnCube()
{
	ACube::OnConstruction(GetTransform());
	
	SetActorLocation(RespawnLocation);
	SetActorRotation(RespawnRotation);
}

void ACube::SetColor(DTypes::DCOLOR dColor)
{
	DColor = dColor;

	if (CubeMesh && CubeMaterials.Num() > DColor)
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